/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:07:02 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/09 16:23:35 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int	fdf_init_main_variables(int *ret, pid_t pids[2], int fds[2])
{
	ret = 0;
	pids[0] = -1;
	pids[1] = -1;
	fds[0] = -1;
	fds[1] = -1;
	return (1);
}

int	check_arg_number(int nargs)
{
	if (nargs != 5)
		exit(1);
	return (1);
}

void	update_err_and_file_err(int *err, int err_no)
{
	*err = err_no;
	return ;
	if (*err != 13 && *err != err_no)
		*err = err_no;
}
