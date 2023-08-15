# include <minishell.h>

int check_prnt_direrr(char *dir) // TODO totaly useless
{
	int err;
	struct stat	*restrict stat_buf;

	if (access(dir, F_OK) < 0)
	{
		err = errno;
		ft_printf(2, "cd: %s: No such file or directory\n", dir);
		return (1);
	}
	stat_buf = malloc(sizeof(stat_buf));
	if (stat(dir, stat_buf) == 0)
	{
		if (stat_buf->st_mode != 16877) // https://man7.org/linux/man-pages/man7/inode.7.html ## look for "The file type and mode"
		{
			ft_printf(2, "cd: %s: Not a directory\n", dir);
			return (1);
			free(stat_buf);
		}
		free(stat_buf);
	}
	else //TODO DELETE
	{
		ft_printf(1, "SEMBLA QUE ALGO HA ANAT MALAMENT (blt_cd.c: check_prnt_direrr)");
		ft_printf(2, "SEMBLA QUE ALGO HA ANAT MALAMENT (blt_cd.c: check_prnt_direrr)");
	}
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
	int	err;

	//TODO modifie env
	if (argc < 2)
		return (0);
	err = check_prnt_direrr(argv[1]);
	if (err)
	{
		return (err);
	}
	if(chdir(argv[1]) < 0)
	{
		err = errno;
		ft_printf(2, "cd: %s: ", argv[1]);
		perror(NULL);
		ft_printf(2, "\n");
		return (err);
		
	}

	 
	return (1);
}
