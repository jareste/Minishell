/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/15 03:36:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	redirect_in(int fd)
{
	if (close(fd) == 0)
		printf("::::::::::::::c\n");
	return (0);

}

int	executor(t_tokens *exp_tok)
{
	size_t	i;
	// int		type;
	int		flag;

	i = 0;
	flag = 1;
	while (i < exp_tok->size)
	{
		// type = exp_tok->words[i]->type;
		// if (type == INPUT)
		// 	redirect_in(fd);
		// if (type == OUTPUT)
		// 	redirect_out;
		// if (type >= PIPE)
		// {
		// 	if (flag == 1)
		// 		return (1);//error
		// 	flag = 1;
		// }
		i++; //PH
	}
 	return (0);
}
