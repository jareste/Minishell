/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/06 02:20:12 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	expander(t_tokens *tokens)
{
	int	i;
	char *str;

	i = 0;
	while (tokens->words[i])
	{
		str = tokens->words[i]->word;
		printf("%s\n", str);
		// if ()
		i++;
	}
	return (0);
}
