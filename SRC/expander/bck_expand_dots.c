/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:18:45 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 16:02:28 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static size_t	dst_tobreak(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ' && !break_ch(str[i]))
		i++;
	return (i);
}

int	expand_dots(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	char	*str;
	int		j;

	str = tokens->words[i]->word;
	if (tokens->words[i]->type == 1)
		msh_add_word(exp_tok, str, ft_strlen(str), 0);
	else
	{
		if (dst_tobreak(str) < tokens->words[i]->len);
		//aqui tengo que gestionar una string con br ch as $.
		else;
		//aqui simplemente gestiono string normal.
		j = 0;
		// while (str[j])
		// {
			// if (str[j] == '$')
		
		// }
	}
		return (1);
}