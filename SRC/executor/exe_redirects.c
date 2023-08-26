/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:13:57 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 22:15:43 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	redirect_in(char *str, t_cmd *cmd)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "%s: ", str);
		perror(NULL);
		cmd->err = 1;
		return (1);
	}
	else if (fd > 0)
		dup2(fd, STDIN_FILENO);
	close(fd);
	cmd->flag_red[IN] = 1;
	return (0);
}

int	redirect_out(char *str, t_cmd *cmd, int type)
{
	int	fd;

	fd = -1;
	if (type == OUTPUT)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_printf(2, "%s: ", str);
		perror(NULL);
		return (1);
	}
	if (fd > 2)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd->flag_red[OUT] = 1;
	return (0);
}

int	redirect_hdc(int fd, t_cmd *cmd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	cmd->flag_red[IN] = 1;
	return (0);
}
