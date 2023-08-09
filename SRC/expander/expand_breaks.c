/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_breaks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:11:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 02:03:02 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static char	*expand_dollar(t_tokens *tokens, int i)
{
	char	*str;
	int		type;


	str = NULL;
	printf("%s\n", getenv("HOME"));
	type = tokens->words[i + 1]->type;
	// str = tokens->words[i + 1]->word;
	if (type == 4)
		return (str);
	if (tokens->words[i + 1]->type != 0)
		return (str);
	str = tokens->words[i]->word;
	return (str);
}

static int	expand_in(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	int		type;
	char	ch;
	char	*dst;
	char	*src[2];

	type = tokens->words[i + 1]->type;
	ch = tokens->words[i + 1]->word[0];
	src[0] = tokens->words[i]->word;
	if (type == 3 && ch == '$')
		src[1] = expand_dollar(tokens, (i + 1));
	if (type != 3)
	{
		if (ch == ' ' && type == 4)
			i++;
		src[1] = tokens->words[i + 1]->word;
	}
	if (!src[1])
		return (i + 1);
	dst = ft_strjoin(src[0], src[1]);
	msh_add_word(exp_tok, dst, ft_strlen(dst), 0);
	free(dst);
	return (i + 1);
}

static int	expand_out(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	int		type;
	char	ch;
	char	*dst;
	char	*src[2];

	type = tokens->words[i + 1]->type;
	ch = tokens->words[i + 1]->word[0];
	if (type == 3 && ch == '$')
		expand_dollar(tokens, (i + 1));
	if (type != 3)
	{
		src[0] = tokens->words[i]->word;
		if (ch == ' ' && type == 4)
			i += 2;
		else
			i += 1;
		src[1] = tokens->words[i]->word;
		dst = ft_strjoin(src[0], src[1]);
		msh_add_word(exp_tok, dst, ft_strlen(dst), 0);
		free(dst);
	}
	return (i);
}



int	expand_break(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	int		j;
	char	*str;

	j = 0;
	str = tokens->words[i]->word;
	if (str[0] == '|')
		return (1);
	// else if (str[0] == '$')
	// 	i += expand_dollar(tokens, i);
	else if (str[0] == '<')
		i = expand_in(tokens, exp_tok, i);
	else if (str[0] == '>')
		i = expand_out(tokens, exp_tok, i);
	return (i);
}
