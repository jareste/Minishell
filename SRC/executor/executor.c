/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/15 08:57:13 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	redirect_in(int fd)
{
	if (close(fd) == 0)
		printf("::::::::::::::c\n");
	return (0);

}

int	redirect_out(int fd)
{
	close (fd);
	return 1;
}

void	init_cmd(t_tokens *t_exp, t_cmd *cmd)
{
	size_t	i;

	cmd->fd_in[0] = 0;
	cmd->fd_out[0] = 1;
	cmd->t_exp = t_exp;
	i = 0;
	while (i < t_exp->size)
	{
		if (t_exp->words[i]->type >= 3)
			break ;
		
	}
}

int	executor(t_tokens *exp_tok)
{
	size_t	i;
	int		type;
	int		flag;
	// t_cmd	cmd;

int fd = 1;
	i = 0;
	flag = 1;
	while (i < exp_tok->size)
	{
		type = exp_tok->words[i]->type;
		if (type == INPUT)
			redirect_in(fd);
		if (type == OUTPUT)
			redirect_out(fd);
		if (type >= PIPE)
		{
			if (flag == 1)
				return (1);//error
			flag = 1;
		}
		i++; //PH
	}
 	return (0);
}
