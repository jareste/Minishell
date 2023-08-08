/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 00:42:06 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"


int	expander(t_tokens *tokens, t_tokens *exp_tok)
{
	int		i;
	int		type;

	i = 0;
	while (tokens->words[i])
	{
		type = tokens->words[i]->type;
		if (type == 3)
			i = expand_break(tokens, exp_tok, i);
		// if (type == 2 || type == 1)
			// expand_dots();
		i++;
	}
	msh_mount_matrix(exp_tok);
	return (0);
}
