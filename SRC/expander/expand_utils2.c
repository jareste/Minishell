/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:08:57 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 21:31:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	count_pipes(t_tokens *tokens)
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

static	int	aux_exp_type(t_tokens *tokens, int i, int type)
{
	if (tokens->words[i - 1]->word[0] == '<' && \
	tokens->words[i - 2]->word[0] == '|')
		type = INPIPE;
	if (tokens->words[i - 1]->word[0] == '>' && \
	tokens->words[i - 2]->word[0] == '|')
		type = OUTPIPE;
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
	tokens->words[i - 2]->word[0] == '>' && i > 2 \
	&& tokens->words[i - 3]->word[0] == '|')
		type = APPENDPIPE;
	return (type);
}

void	new_tokens(t_tokens *exp_tok, char *str, int type)
{
	msh_add_word(exp_tok, str, ft_strlen(str), type);
	if (str[0])
		free(str);
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
