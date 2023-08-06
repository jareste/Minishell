/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/06 13:39:05 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static	int	check_format(t_word *word, char *str)
{
	if (break_ch(str[0]))
	{
		return (1);
	}
	if (str[0] == '\'')
		return (0);
}

int	expander(t_tokens *tokens)
{
	int		i;
	char	*str;

	i = 0;
	while (tokens->words[i])
	{
		if (tokens->words[i]->type == 1)
			i++;
		else
		{
			str = tokens->words[i]->word;
			if ()
			i++;
		}
	}
	return (0);
}
