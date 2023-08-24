/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/24 20:09:26 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	redirect_in(char *str, t_cmd *cmd)
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

static int	redirect_out(char *str, t_cmd *cmd, int type)
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

int	dst_topipe(t_tokens *exp_tok, size_t i)
{
	int	j;

	j = 0;
	while (i < exp_tok->size)
	{
		if (exp_tok->words[i]->type < PIPE)
			j++;
		else if (exp_tok->words[i]->type >= PIPE)
			break ;
		i++;
	}
	return (j);
}

int	init_cmd(t_tokens *exp_tok, t_cmd *cmd, size_t i, int j)
{
	int	type;

	(0 || (cmd->flag_red[IN] = 0) || (cmd->flag_red[OUT] = 0) || (cmd->err = 0));
	(0 || (j = 0) || (cmd->err_flag = 0) || (cmd->exp_tok = exp_tok));
	if (exp_tok->words[i]->type >= PIPE)
		exp_tok->words[i]->type -= PIPE;
	cmd->args = ft_calloc(sizeof(char *), dst_topipe(exp_tok, i) + 1);
	while (i < exp_tok->size)
	{
		type = exp_tok->words[i]->type;
		if (exp_tok->words[i]->type >= PIPE && j > 0)
			break ;
		if (type == INPUT || type == INPIPE)
			if (redirect_in(exp_tok->words[i]->word, cmd))
				return (1);
		if (type == OUTPUT || type == OUTPIPE || \
		type == APPEND || type == APPENDPIPE)
			if (redirect_out(exp_tok->words[i]->word, cmd, type))
				return (1);
		if (type == NONE)
			cmd->args[j++] = ft_strdup(exp_tok->words[i]->word);
		i++;
	}
	cmd->argc = j;
	return (0);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	if (cmd->args)
		free(cmd->args);
}

int	check_blt(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->flag_red[IN] = 0;
	cmd->flag_red[OUT] = 0;
	while (cmd->args[0][i])
		ft_tolower(cmd->args[0][i++]);
	if (ft_strncmp("echo", cmd->args[0], ft_strlen("echo") + 1) == 0)
		return (blt_echo(cmd->argc, cmd->args));
	else if (ft_strncmp("cd", cmd->args[0], ft_strlen("cd") + 1) == 0)
		return (blt_cd(cmd->argc, cmd->args));
	else if (ft_strncmp("pwd", cmd->args[0], ft_strlen("pwd") + 1) == 0)
		return(blt_pwd());
	else if (ft_strncmp("export", cmd->args[0], ft_strlen("export") + 1) == 0)
		printf("export\n");//blt_export;
	else if (ft_strncmp("unset", cmd->args[0], ft_strlen("unset") + 1) == 0)
		printf("unset\n");//blt_unset;
	else if (ft_strncmp("env", cmd->args[0], ft_strlen("env") + 1) == 0)
		printf("env\n");//return (blt_env(cmd->env, NULL, 0));
	else if (ft_strncmp("exit", cmd->args[0], ft_strlen("exit") + 1) == 0)
		exit(blt_exit(cmd->argc, cmd->args));
	return (127);
}


int	call(t_cmd *cmd)
{
	char	**paths;
	char	*path_test;
	int		i;
	int		ret;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path_test = ft_strjoin(ft_strjoin(paths[i], "/"), cmd->args[0]);
		ret = execve(path_test, cmd->args, NULL);
		free(path_test);
		if (ret == 0)
		{
			free(paths);
			return (0);
		}
		i++;
	}
	free(paths);
	return (1);
}

int	call_wo_path(t_cmd *cmd)
{
	if (execve(cmd->args[0], cmd->args, NULL) == -1)
		return (1);
	return (0);
}

///EXEC CMD

int	exe_cmd(t_cmd *cmd)
{
	if (check_blt(cmd) == 0)
		return (0);//ss
	else if (call(cmd) == 0)
		return (0);//ss
	else if (call_wo_path(cmd) == 0)
		return (0);//s
	else
		ft_printf(2, "%s: command not found\n", cmd->args[0]);//s
	return (127);
}

int	is_blt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_tolower(str[i++]);
	if (ft_strncmp("echo", str, ft_strlen("echo") + 1) == 0)
		return (0);
	else if (ft_strncmp("cd", str, ft_strlen("cd") + 1) == 0)
		return (0);
	else if (ft_strncmp("pwd", str, ft_strlen("pwd") + 1) == 0)
		return(0);
	else if (ft_strncmp("export", str, ft_strlen("export") + 1) == 0)
		return (0);
	else if (ft_strncmp("unset", str, ft_strlen("unset") + 1) == 0)
		return (0);
	else if (ft_strncmp("env", str, ft_strlen("env") + 1) == 0)
		return (0);
	else if (ft_strncmp("exit", str, ft_strlen("exit") + 1) == 0)
		return (0);
	return (1);

}


int	executor(t_tokens *exp_tok)
{
	size_t	i;
	t_cmd	cmd;
	pid_t	pid;
	int		status;
	int		j;

	j = 0;
	i = 0;
	// pid = malloc(sizeof(pid_t) * exp_tok->pipe_n + 1);
	cmd.pipe_fd[IN] = -1; // 2fds, 0 == old, 1 == NEW
	cmd.pipe_fd[OUT] = -1;
	cmd.prev_pipe[IN] = -1;
	cmd.prev_pipe[OUT] = -1;
	cmd.init_fd[OUT]= dup(STDOUT_FILENO);
	cmd.init_fd[IN] = dup(STDIN_FILENO);
	while (i < exp_tok->size)
	{
		if (init_cmd(exp_tok, &cmd, i, 0))
			cmd.err_flag = 1;
		if (exp_tok->pipe_n != 0 && j < exp_tok->pipe_n && !cmd.err_flag) //i < exp_tok->size - 1)
			pipe(cmd.pipe_fd);
		if (cmd.argc && (is_blt(cmd.args[0]) || (!is_blt(cmd.args[0]) && exp_tok->pipe_n != 0))) // si es blt i no hay pipe va directo stdout.
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd.err_flag == 1)
					exit(1);
				init_signals(N_INTERACT);
				if (i > 0 && exp_tok->pipe_n != 0)
				{
					close(cmd.prev_pipe[OUT]);
					if (cmd.flag_red[IN] == 0)
						dup2(cmd.prev_pipe[IN], STDIN_FILENO);
					close(cmd.prev_pipe[IN]);
				}
				if (exp_tok->pipe_n != 0)
				{
					close(cmd.pipe_fd[IN]); // TODO no se si es possible que tanci el stdin en cas de que no s'hagi innicialitzat
					if (cmd.flag_red[OUT] == 0)// && j < exp_tok->pipe_n)
					{
						if (j == exp_tok->pipe_n)
							dup2(cmd.init_fd[OUT], STDOUT_FILENO);
						else
							dup2(cmd.pipe_fd[OUT], STDOUT_FILENO);
					}
					close(cmd.pipe_fd[OUT]);
				}
				exit(exe_cmd(&cmd));
			}
			if (i > 0 && cmd.prev_pipe[IN] > 0)
			{
				close(cmd.prev_pipe[IN]);
				close(cmd.prev_pipe[OUT]);
			}
			if (i < exp_tok->size - 1)
			{
				cmd.prev_pipe[IN] = cmd.pipe_fd[IN];
				cmd.prev_pipe[OUT] = cmd.pipe_fd[OUT];
			}
			if (cmd.err > 0)
				break ;
			cmd.flag_red[OUT] = 0;
			cmd.flag_red[IN] = 0;
		}
		else
			if (cmd.argc)
				cmd.err = check_blt(&cmd);
		j++;
		i += dst_topipe(exp_tok, i);
		free_cmd(&cmd);
	}
	while (j >= 0)
	{
		j--;
		if (pid == wait(&status))
		{
			if (WIFEXITED(status))
				cmd.err = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					cmd.err = 130;
				else if (WTERMSIG(status) == SIGQUIT)
					(1 && (cmd.err = 131) && (printf("Quit: 3\n")));
			}
		}
	}
	dup2(cmd.init_fd[OUT], STDOUT_FILENO);
	dup2(cmd.init_fd[IN], STDIN_FILENO);
	close(cmd.init_fd[OUT]);
	close(cmd.init_fd[IN]);
	return (cmd.err);
}

///////////////////////// CHECK NO FD OPEN /////////////////////////
	// int hola = open("JAJAJA", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// printf("fd_check no fdopen:::::::::::%i\n", hola);
	// close (hola);
///////////////////////// CHECK NO FD OPEN /////////////////////////
