/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:22:25 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/18 13:14:54 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>

static int	wait_end(pid_t pids[2], int fds[2], int ppe[2], int *ret);

//pid_t	call(char **argv, char **envp, int fds[3], char **oargv)
pid_t	call(t_cmd *cmd)
{
	char	*path;
	pid_t	pid;
	int		exit_val;

	pid = fork();
	exit_val = 0;
	if (!pid)
	{
		close(fds[2]);
		close(cmd->prev_pipe[1]);
		close(cmd->fd_in[0]);
		path = get_path(cmd->args[0], envp); //env
		if (!path)
			exit_val = 1;
//			exit_val = ppx_patherr(oargv, envp, path, argv);
		else if (!path || 0 > dup2(cmd->prev_pipe[0], 0) || 0 > dup2(comd->fd_in[1], 1)) //else if (!path || 0 > dup2(fds[0], 0) || 0 > dup2(fds[1], 1)) 
			exit_val = errno;
		else if (execve(path, cmd->args, envp) == -1) //env
			exit_val = errno;
		if (path)
			free(path);
		exit(exit_val);
	}
	return (pid);
}
/*
int	load_stdio(int tuberia[2], int fds[2], char *file_names[2], char *program)
{
	int	err;

	err = 0;
	fds[0] = open(file_names[0], O_RDONLY);
	if (fds[0] == -1)
	{
		err = errno;
		ft_printf("%s: %s: %s\n", program, file_names[0], strerror(err));
		close_fds(&tuberia[1], NULL, NULL, NULL);
		err = 0;
	}
	fds[1] = open(file_names[1], O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	err = errno;
	if (fds[1] == -1)
	{
		err = errno;
		if (!access(file_names[1], F_OK))
			err = 1;
		ft_printf("%s: %s: %s\n", program, file_names[1], strerror(err));
		close_fds(&tuberia[0], NULL, NULL, NULL);
	}
	return (err);
}

int	load_fds(int tuberia[2], int fds[2], char *file_names[2], char *prg_opts[2])
{
	int		err;
	char	*program;

	if (prg_opts[0])
		program = prg_opts[0];
	else
		program = prg_opts[1];
	program = ft_strchr(program, '/') + 1;
	err = 0;
	if (pipe(tuberia))
	{
		err = errno;
		perror(NULL);
		close_fds(&tuberia[0], &tuberia[1], &fds[0], &fds[1]);
		return (err);
	}
	err = load_stdio(tuberia, fds,
			(char *[]){file_names[0], file_names[1]}, program);
	return (err);
}

static int	wait_end(pid_t pids[2], int fds[2], int ppe[2], int *ret)
{
	pid_t	pid;
	int		info;

	while (pids[1] != -1)
	{
		pid = wait(&info);
		*ret = WEXITSTATUS(info);
		if (pid == pids[1])
		{
			close_fds(&fds[1], &ppe[0], NULL, NULL);
			pids[1] = -1;
		}
		else
		{
			close_fds(&fds[0], &ppe[1], NULL, NULL);
			pids[0] = -1;
		}
	}
	if (pids[0] != -1)
	{
		close_fds(&fds[0], &ppe[1], NULL, NULL);
		pids[0] = -1;
	}
	return (*ret);
}

int	main(int argc, char **argv, char **envp)
{
	int		tuberia[2];
	int		fds[2];
	pid_t	pids[2];
	char	**args[2];
	int		ret;

	ret = check_arg_number(argc) && fdf_init_main_variables(&ret, pids, fds);
	ret = load_fds(tuberia, fds, (char *[]){argv[1], argv[4]},
			(char *[]){get_env(envp, "SHELL"), argv[0]});
	args[0] = ppx_split(argv[2]);
	if (!args[0])
		close_fds(&fds[0], &tuberia[1], NULL, NULL);
	if (fds[0] != -1)
		pids[0] = call(args[0], envp,
				(int []){fds[0], tuberia[1], tuberia[0]}, argv);
	args[1] = ppx_split(argv[3]);
	if (!args[1])
		close_fds(&fds[1], &tuberia[0], NULL, NULL);
	if (fds[1] != -1)
		pids[1] = call(args[1], envp,
				(int []){tuberia[0], fds[1], tuberia[1]}, argv); 
	ret = wait_end(pids, fds, tuberia, &ret);
	ppx_free_matrix(args[0]);
	ppx_free_matrix(args[1]);
	return (ret);
}
*/
