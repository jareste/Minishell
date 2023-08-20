/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 03:54:26 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/20 04:01:08 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

static int check_prnt_direrr(char *dir) // TODO totaly useless
{
	int err;
	struct stat	*restrict stat_buf;

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
	// else //TODO DELETE
	// {
	// 	// ft_printf(1, "SEMBLA QUE ALGO HA ANAT MALAMENT (blt_cd.c: check_prnt_direrr)");
	// 	ft_printf(2, "SEMBLA QUE ALGO HA ANAT MALAMENT (blt_cd.c: check_prnt_direrr)");
	// }
	if (access(dir, X_OK) < 0)
	{
		err = errno;
		ft_printf(2, "cd: %s: Permission denied\n", dir);
		return (err);
	}
	return (0);
}

int blt_cd(int argc, char** argv)
{
	int		err;
	char	*dir;

	//TODO modifie env
	if (argc == 1) //if argc == 1 no ha de retornar 1, sino anar a HOME.
		dir = ft_strdup(getenv("HOME"));
	else
		dir = ft_strdup(argv[1]);
	err = check_prnt_direrr(dir);
	if (err)
	{
		return (err);
	}
	if(chdir(dir) < 0)
	{
		err = errno;
		ft_printf(2, "cd: %s: ", dir);
		perror(NULL);
		ft_printf(2, "\n");
		free(dir);
		return (err);
		
	}
	free(dir);
	return (0);
}
