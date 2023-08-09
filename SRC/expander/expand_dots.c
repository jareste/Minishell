/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:18:45 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 04:25:57 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	expand_dots(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	char	*str;
	int		j;

	str = tokens->words[i]->word;
	if (tokens->words[i]->type == 1)
		msh_add_word(exp_tok, str, ft_strlen(str), 0);
	// else
	// {
		j = 0;
	// 	while (str[j])
	// 	{
	// 		if (str[j] == '$')
		
	// 	}
	// }
		return (1);
}