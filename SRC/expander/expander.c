/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/06 11:26:51 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static	int	check_format(t_word *word, char *str)
{
	if (break_ch(str[0]))
}

int	expander(t_tokens *tokens)
{
	int	i;
	char *str;

	i = 0;
	while (tokens->words[i])
	{
		str = tokens->words[i]->word;
		printf("%s\n", str);
		if ()
		i++;
	}
	return (0);
}
