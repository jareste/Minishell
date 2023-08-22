/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 03:54:26 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/22 15:03:55 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_prnt_direrr(char *dir)
{
	int						err;
	struct stat	*restrict	stat_buf;

	if (access(dir, F_OK) < 0)
	{
		err = errno;
		ft_printf(2, "cd: %s: No such file or directory\n", dir);
		return (1);
	}
	stat_buf = malloc(sizeof(struct stat));
	if (stat(dir, stat_buf) == 0)
	{
		if (!S_ISDIR(stat_buf->st_mode)) 
		//modificada condicio, macro de llibreria <sys/stat.h>
		{
			ft_printf(2, "cd: %s: Not a directory\n", dir);
			free(stat_buf);
			return (1);
		}
		free(stat_buf);
	}
	if (access(dir, X_OK) < 0)
	{
		err = errno;
		ft_printf(2, "cd: %s: Permission denied\n", dir);
		return (err);
	}
	return (0);
}

int	blt_cd(int argc, char **argv)
{
	char	*dir;

	//TODO modifie env
	if (argc == 1 || (ft_strncmp("~", argv[1], ft_strlen("~")) == 0)) //if argc == 1 no ha de retornar 1, sino anar a HOME.
		dir = ft_strdup(getenv("HOME"));
	else
		dir = ft_strdup(argv[1]);
	g_msh.err = check_prnt_direrr(dir);
	if (g_msh.err)
	{
		return (g_msh.err);
	}
	if (chdir(dir) < 0)
	{
		g_msh.err = 1;
		ft_printf(2, "cd: %s: ", dir);
		perror(NULL);
		free(dir);
		return (g_msh.err);
	}
	free(dir);
	return (0);
}
