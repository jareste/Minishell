/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_breaks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:11:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 00:41:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

// static int	expand_dollar(t_tokens *tokens, int i)
// {
// 	char	*next_str;
	
// 	if (!tokens->words[i + 1]->word)
// 		return (1);
// 	if (!tokens->words[i + 1]->type != 0)
// 		return (1);
// 	next_str = tokens->words[i]->word;
// 	//ahora tengo que buscar next_str en ENV y la coincidencia guardarla
// 	//expandida.
// }

static int	expand_in(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	int		type;
	char	ch;
	char	*dst;
	char	*src[2];

	type = tokens->words[i + 1]->type;
	ch = tokens->words[i + 1]->word[0];
	// if (type == 3 && ch == '$')
		// expand_dollar(tokens, (i + 1));
	if (type != 3)
	{
		src[0] = tokens->words[i]->word;
		if (ch == ' ' && type == 4)
			src[1] = tokens->words[i + 2]->word;
		else
			src[1] = tokens->words[i + 1]->word;
		dst = ft_strjoin(tokens->words[i]->word, src[1]);
		printf("%s\n", dst);
		msh_add_word(exp_tok, dst, ft_strlen(dst), 0);
		msh_mount_matrix(exp_tok);
		msh_print_tokens(exp_tok);



		free(dst);
	}
	return (0);
}

// static int	expand_out();




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
		i += expand_in(tokens, exp_tok, i);
	// else if (str[0] == '>')
		// i += expand_out();
	return (i);
}
