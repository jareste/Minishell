/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_breaks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:11:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 03:10:17 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static char	*expand_dollar(t_tokens *tokens, int i)
{
	char	*str;
	int		type;

	type = tokens->words[i + 1]->type;
	if (type == 4)
	{
		str = "$";
		return (str);
	}
	str = tokens->words[i + 1]->word;
	return (getenv(str));
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
	if (ch == ' ' && type == 4)
	{
		i++;
		ch = tokens->words[i + 1]->word[0];
		type = tokens->words[i + 1]->type;
	}
	if (type == 3 && ch == '$')
		src[1] = expand_dollar(tokens, (i + 1));
	i++;
	if (type != 3)
		src[1] = tokens->words[i]->word;
	dst = ft_strjoin(src[0], src[1]);
	msh_add_word(exp_tok, dst, ft_strlen(dst), 0);
	free(dst);
	// free_src(src);// hay que liberar SRC, pero no se como.
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
	src[0] = tokens->words[i]->word;
	if (ch == ' ' && type == 4)
	{
		i++;
		ch = tokens->words[i + 1]->word[0];
		type = tokens->words[i + 1]->type;
	}
	if (type == 3 && ch == '$')
		src[1] = expand_dollar(tokens, (i + 1));
	i++;
	if (type != 3)
		src[1] = tokens->words[i]->word;
	dst = ft_strjoin(src[0], src[1]);
	msh_add_word(exp_tok, dst, ft_strlen(dst), 0);
	free(dst);
	// free_src(src);// hay que liberar SRC, pero no se como.
	return (i + 1);
}

static int	do_dollar(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	char	*str;

	printf("he entrau\n");
	str = expand_dollar(tokens, i);
	msh_add_word(exp_tok, str, ft_strlen(str), 0);
	return (i + 1);
}

int	expand_break(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	int		j;
	char	*str;

	j = 0;
	str = tokens->words[i]->word;
	printf("i:::::%i\n", i);
	if (str[0] == '|')
		return (1);
	else if (str[0] == '$')
		i = do_dollar(tokens, exp_tok, i);
	else if (str[0] == '<')
		i = expand_in(tokens, exp_tok, i);
	else if (str[0] == '>')
		i = expand_out(tokens, exp_tok, i);
	return (i);
}
