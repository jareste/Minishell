/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 20:32:16 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	dst_tobreak(t_tokens *tokens, size_t i)
{
	int		j;
	char	*str;

	j = 0;
	str = tokens->words[i]->word;
	while (str[0] && str[0] != '<' && \
	str[0] != '>' && str[0] != '|')
	{
		if (str[0] == ' ' && tokens->words[i]->type == 4)
			break ;
		j++;
		i++;
		if (tokens->size <= i)
			break ;
		str = tokens->words[i]->word;
	}
	return (j);
}

static int	is_break_exp(char ch, int type)
{
	if (ch == ' ' && type != 4)
		return (0);
	if (ch == ' ' || ch == '<' || ch == '>' || ch == '|')
		return (1);
	return (0);
}

static	void	ft_free(char **matrix, int len)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
		if (i > len)
			break ;
	}
	free(matrix);
}

static void	new_tokens(t_tokens *exp_tok, char *str, int type)
{
	msh_add_word(exp_tok, str, ft_strlen(str), type);
	if (str[0])
		free(str);
}

static	int	aux_exp_type(t_tokens *tokens, int i, int type)
{
	if (tokens->words[i - 1]->word[0] == '<' && \
	tokens->words[i - 2]->word[0] == '|')
		type = INPIPE;
	if (tokens->words[i - 1]->word[0] == '>' && \
	tokens->words[i - 2]->word[0] == '|')
		type = OUTPIPE;
	// if (i > 2)
	// {
	if (tokens->words[i - 1]->word[0] == '<' && \
	tokens->words[i - 2]->word[0] == '<')
		type = HEREDOC;
	if (tokens->words[i - 1]->word[0] == '>' && \
	tokens->words[i - 2]->word[0] == '>')
		type = APPEND;
	if (tokens->words[i - 1]->word[0] == '<' && \
	tokens->words[i - 2]->word[0] == '<' && i > 2 \
	&& tokens->words[i - 3]->word[0] == '|')
		type = HEREDOCPIPE;
	if (tokens->words[i - 1]->word[0] == '>' && \
	tokens->words[i - 2]->word[0] == '>' && i > 2\
	&& tokens->words[i - 3]->word[0] == '|')
		type = APPENDPIPE;
	// }
	return (type);
}

int	exp_type(t_tokens *tokens, int i)
{
	int	type;

	type = NONE;
	if (i >= 1)
	{
		if (i > 1 && tokens->words[i - 1]->word[0] == ' ')
		{
			tokens->words[i - 1]->word[0] = tokens->words[i - 2]->word[0];
			if (i > 2)
				tokens->words[i - 2]->word[0] = tokens->words[i - 3]->word[0];
			else if (i == 2)
				tokens->words[i - 2]->word[0] = '\0';
		}
		if (tokens->words[i - 1]->word[0] == '<')
			type = INPUT;
		if (tokens->words[i - 1]->word[0] == '>')
			type = OUTPUT;
		if (tokens->words[i - 1]->word[0] == '|')
			type = PIPE;
		if (i > 1)
			type = aux_exp_type(tokens, i, type);
	}
	return (type);
}

static int	count_pipes(t_tokens *tokens)
{
	size_t	i;
	int		pipes;

	i = 0;
	pipes = 0;
	while (i < tokens->size)
	{
		if (tokens->words[i]->word[0] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}
int	expander(t_tokens *tokens, t_tokens *exp_tok, int err[2])
{
	t_aux_exp	aux;

	aux.type = 0;
	aux.i = 0;
	exp_tok->pipe_n = count_pipes(tokens);
	while (aux.i < tokens->size)
	{
		aux.len = dst_tobreak(tokens, aux.i);
		aux.str = ft_calloc(aux.len + 1, sizeof(char *));
		aux.type = exp_type(tokens, aux.i);
		aux.j = 0;
		while (!is_break_exp(tokens->words[aux.i]->word[0], tokens->words[aux.i]->type))
		{
			if (tokens->words[aux.i]->type == 2)
				aux.str[aux.j] = expand_dots(tokens, aux.i, 0, "\0");
			else if (tokens->words[aux.i]->type == 3)
			{
				aux.str[aux.j] = ft_strdup(expand_dollar(tokens, aux.i, err));
				aux.i++;
			}
			else
				aux.str[aux.j] = ft_strdup(tokens->words[aux.i]->word);
			aux.j++;
			aux.i++;
			if (tokens->size <= aux.i)
				break ;
		}
		if (aux.str[0])
		{
			aux.src = merge_matrix(aux.str, aux.len);
			new_tokens(exp_tok, aux.src, aux.type);
			ft_free(aux.str, aux.len);
		}
		aux.i++;
	}
	msh_mount_matrix(exp_tok);
	return (0);
}
