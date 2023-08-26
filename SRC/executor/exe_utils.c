/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:32:19 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 23:39:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	ft_close(t_cmd *cmd)
{
	dup2(cmd->init_fd[OUT], STDOUT_FILENO);
	dup2(cmd->init_fd[IN], STDIN_FILENO);
	close(cmd->init_fd[OUT]);
	close(cmd->init_fd[IN]);
}

void	ft_init_fd(t_cmd *cmd, t_tokens *exp_tok)
{
	cmd->pipe_fd[IN] = -1;
	cmd->pipe_fd[OUT] = -1;
	cmd->prev_pipe[IN] = -1;
	cmd->prev_pipe[OUT] = -1;
	cmd->init_fd[OUT] = dup(STDOUT_FILENO);
	cmd->init_fd[IN] = dup(STDIN_FILENO);
	if (do_hdc(exp_tok))
		cmd->err_flag = 1;
}

void	do_fork(t_tokens *exp_tok, t_cmd *cmd, int i, int j)
{
	if (cmd->err_flag == 1)
		exit(1);
	init_signals(N_INTERACT);
	if (i > 0 && exp_tok->pipe_n != 0)
	{
		close(cmd->prev_pipe[OUT]);
		if (cmd->flag_red[IN] == 0)
			dup2(cmd->prev_pipe[IN], STDIN_FILENO);
		close(cmd->prev_pipe[IN]);
	}
	if (exp_tok->pipe_n != 0)
	{
		close(cmd->pipe_fd[IN]);
		if (cmd->flag_red[OUT] == 0)
		{
			if (j == exp_tok->pipe_n)
				dup2(cmd->init_fd[OUT], STDOUT_FILENO);
			else
				dup2(cmd->pipe_fd[OUT], STDOUT_FILENO);
		}
		close(cmd->pipe_fd[OUT]);
	}
	exit(exe_cmd(cmd, cmd->env));
}

void	wait_process(t_cmd *cmd, pid_t pid, int j)
{
	int	status;

	while (j >= 0)
	{
		j--;
		if (pid == wait(&status))
		{
			if (WIFEXITED(status))
				cmd->err = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					cmd->err = 130;
				else if (WTERMSIG(status) == SIGQUIT)
					(1 && (cmd->err = 131) && (printf("Quit: 3\n")));
			}
		}
	}
}

void	close_pipe_fd(t_tokens *exp_tok, t_cmd *cmd, size_t i)
{
	if (i > 0 && cmd->prev_pipe[IN] > 0)
	{
		close(cmd->prev_pipe[IN]);
		close(cmd->prev_pipe[OUT]);
	}
	if (i < exp_tok->size - 1)
	{
		cmd->prev_pipe[IN] = cmd->pipe_fd[IN];
		cmd->prev_pipe[OUT] = cmd->pipe_fd[OUT];
	}
	cmd->flag_red[OUT] = 0;
	cmd->flag_red[IN] = 0;
}
