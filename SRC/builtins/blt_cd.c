/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 03:54:26 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 19:25:00 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_prnt_direrr(char *dir)
{
	struct stat	*restrict	stat_buf;

	if (access(dir, F_OK) < 0)
	{
		ft_printf(2, "cd: %s: No such file or directory\n", dir);
		return (1);
	}
	stat_buf = malloc(sizeof(struct stat));
	if (stat(dir, stat_buf) == 0)
	{
		if (!S_ISDIR(stat_buf->st_mode)) 
		{
			ft_printf(2, "cd: %s: Not a directory\n", dir);
			free(stat_buf);
			return (1);
		}
		free(stat_buf);
	}
	if (access(dir, X_OK) < 0)
	{
		ft_printf(2, "cd: %s: Permission denied\n", dir);
		return (errno);
	}
	return (0);
}

int	blt_cd(int argc, char **argv, t_env **env)
{
	char	*dir;
	int		err;
	//TODO modifie env
	
	err = 0;
	if (argc == 1)
		dir = ft_getenv(*env, "HOME");
	else
		dir = ft_strdup(argv[1]);
	err = check_prnt_direrr(dir);
	if (err)
		return (err);
	if (chdir(dir) < 0)
	{
		ft_printf(2, "cd: %s: ", dir);
		perror(NULL);
		free(dir);
		return (1);
	}
	free(dir);
	return (0);
}
