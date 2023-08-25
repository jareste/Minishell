/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/24 17:39:10 by jareste-         ###   ########.fr       */
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
			tokens->words[i - 1]->word[0] = tokens->words[i - 2]->word[0];
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
	size_t		i;
	size_t		j;
	int			len;
	char		**str;
	char		*src;
	int			type;

	type = 0;
	i = 0;
	exp_tok->pipe_n = count_pipes(tokens);
	while (i < tokens->size)
	{
		len = dst_tobreak(tokens, i);
		str = ft_calloc(len + 1, sizeof(char *));
		type = exp_type(tokens, i);
		j = 0;
		while (!is_break_exp(tokens->words[i]->word[0], tokens->words[i]->type))
		{
			if (tokens->words[i]->type == 2)
				str[j] = expand_dots(tokens, i, 0);
			else if (tokens->words[i]->type == 3) // TODO  el tres tambe pot ser pipe i no la gestiona
			{
				str[j] = ft_strdup(expand_dollar(tokens, i, err)); // TODO Doble dup
				i++;
			}
			else
				str[j] = ft_strdup(tokens->words[i]->word);
			j++;
			i++;
			if (tokens->size <= i)
				break ;
		}
		if (str[0])
		{
			src = merge_matrix(str, len);
			new_tokens(exp_tok, src, type);
			ft_free(str, len);
		}
		i++;
		// printf("after::::::::%i,%c,\n", is_break_exp(tokens->words[i]->word[0]), tokens->words[i]->word[0]);

	}
	msh_mount_matrix(exp_tok);
	return (0);
}
/*
puedo crear una matriz donde primero tengo que contar
la distancia hasta el espacio, despues asignar memoria de la matriz
para luego ir rellenando cada posicion con la string 
expandida correspondiente y finalmente juntar todo en 1 sola.
*/
