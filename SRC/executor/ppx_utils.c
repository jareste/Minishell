/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:35:23 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/18 13:12:09 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (0);
}

void	twk_log(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, str, len);
}

char	*get_env(char **envp, char *var)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], var, len))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + ft_strlen(var));
}

void	print_list(char **list)
{
	while (*list)
	{
		ft_printf(2, "\t>>>%s<<<\n", *list);
		list++;
	}
	ft_printf(2, "END\n");
}

int	close_fds(int *fd1, int *fd2, int *fd3, int *fd4)
{
	if (fd1 && *fd1 >= 0)
		close(*fd1);
	if (fd2 && *fd2 >= 0)
		close(*fd2);
	if (fd3 && *fd3 >= 0)
		close(*fd3);
	if (fd4 && *fd4 >= 0)
		close(*fd4);
	if (fd1)
		*fd1 = -1;
	if (fd2)
		*fd2 = -1;
	if (fd3)
		*fd3 = -1;
	if (fd4)
		*fd4 = -1;
	return (0);
}
