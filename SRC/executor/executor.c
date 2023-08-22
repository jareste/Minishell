/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/22 18:16:31 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	redirect_in(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd > 0)
        dup2(fd, STDIN_FILENO);
	return (0);
}

static int	redirect_out(char *str)
{
	int	fd;

	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > 2)
		dup2(fd, STDOUT_FILENO);
	return (0);
}

int	dst_topipe(t_tokens *exp_tok, size_t i)
{
	int	j;

	j = 0;
	while (i < exp_tok->size)
	{
		if (exp_tok->words[i]->type < 3)
			j++;
		else if (exp_tok->words[i]->type >= 3)
			break ;
		i++;
	}
	return (j);
}

void	init_cmd(t_tokens *exp_tok, t_cmd *cmd, size_t i)
{
	int	j;
	int	type;
	// TODO els fds potser es tindiren que inicialitzar a -1 per saber si realment fan refrencia a un fd
	// cmd-.pipe_fd[0] = 0; // 2fds, 0 == old, 1 == NEW
	// cmd-.pipe_fd[1] = 1; // 2fds, 0 == old, 1 == NEW
	cmd->err = 0;
	cmd->exp_tok = exp_tok;
	if (exp_tok->words[i]->type >= 3)
		exp_tok->words[i]->type -= 3;
	cmd->args = ft_calloc(sizeof(char *), dst_topipe(exp_tok, i) + 1);
	j = 0;
	while (i < exp_tok->size) //esto no sirve (creo) //atm si sirve
	{
		type = exp_tok->words[i]->type;
		if (exp_tok->words[i]->type >= PIPE && j > 0)
			break ;
		else if (type == INPUT || type == INPIPE)
			redirect_in(exp_tok->words[i]->word);
		else if (type == OUTPUT || type == OUTPIPE)
			redirect_out(exp_tok->words[i]->word);
		else
			cmd->args[j++] = ft_strdup(exp_tok->words[i]->word);
		i++;
	}
	cmd->argc = j;
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
		printf("exit\n");//blt_exit;
	return (127);
	//if error return 1;
}


int	call(t_cmd *cmd)
{
	char	*pth;

	pth = ft_strjoin(PATH, cmd->args[0]);
	if (execve(pth, cmd->args, NULL) == -1)
		return (1);
	return (0);
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


int	executor(t_tokens *exp_tok, int err[2])
{
	size_t	i;
	t_cmd	cmd;
	pid_t	pid;
	int		status;
	int		j;
	// int		fdout;
	// int		fdin;
	(void)err;
	j = 0;
	i = 0;
	cmd.pipe_fd[IN] = 0; // 2fds, 0 == old, 1 == NEW
	cmd.pipe_fd[OUT] = 1;
	g_msh.fd[OUT]= dup(STDOUT_FILENO);
	g_msh.fd[IN] = dup(STDIN_FILENO);
	while (i < exp_tok->size)
	{
		if (exp_tok->pipe_n != 0 && j < exp_tok->pipe_n) //i < exp_tok->size - 1)
			pipe(cmd.pipe_fd);
		init_cmd(exp_tok, &cmd, i);
		if (is_blt(cmd.args[0]) || (!is_blt(cmd.args[0]) && exp_tok->pipe_n != 0)) // si es blt i no hay pipe va directo stdout.
		{
			pid = fork();
			if (pid == 0) // es pot gestinar dins del call per tal destalviar linies
				//si, tot aixo va dins una funcio, pero aixo ja ho fare quan sigui validat.
			{
				init_signals(N_INTERACT);
				if (i > 0 && exp_tok->pipe_n != 0)
				{
					close(cmd.prev_pipe[OUT]); // TODO no se si es possible que tanci el stdin en cas de que no s'hagi innicialitzat
					dup2(cmd.prev_pipe[IN], STDIN_FILENO);
					close(cmd.prev_pipe[IN]);
				}
				if (i < exp_tok->size - 1 && exp_tok->pipe_n != 0)
				{
					close(cmd.pipe_fd[IN]); // TODO no se si es possible que tanci el stdin en cas de que no s'hagi innicialitzat
					dup2(cmd.pipe_fd[OUT], STDOUT_FILENO);
					close(cmd.pipe_fd[OUT]);
				}
				exit(exe_cmd(&cmd));
			}
			if (i > 0)
			{
				close(cmd.prev_pipe[IN]);
				close(cmd.prev_pipe[OUT]);
			}
			if (i < exp_tok->size - 1)
			{
				cmd.prev_pipe[IN] = cmd.pipe_fd[IN];
				cmd.prev_pipe[OUT] = cmd.pipe_fd[OUT];
			}
			if (cmd.err != 0)
				return (cmd.err);
		}
		else
			cmd.err = check_blt(&cmd);
		j++;
		i += dst_topipe(exp_tok, i);
		free_cmd(&cmd);
	}
	if (exp_tok->size == 1)
		waitpid(pid, &status, 0);

	// printf("err:::::::::%i,\n", cmd.err);
	while (wait(NULL) > 0)
		i++;
	if (WIFEXITED(status))
		cmd.err = WEXITSTATUS(status);
	dup2(g_msh.fd[OUT], STDOUT_FILENO);
	dup2(g_msh.fd[IN], STDIN_FILENO);
	close(g_msh.fd[OUT]);
	close(g_msh.fd[IN]);
	return (cmd.err);
}

///////////////////////// CHECK NO FD OPEN /////////////////////////
	// int hola = open("JAJAJA", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// printf("fd_check no fdopen:::::::::::%i\n", hola);
	// close (hola);
///////////////////////// CHECK NO FD OPEN /////////////////////////