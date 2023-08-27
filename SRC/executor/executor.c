/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/27 09:28:58 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	aux_init_cmd(t_tokens *exp_tok, t_cmd *cmd, size_t i, int type)
{
	if (type == INPUT || type == INPIPE)
		return (redirect_in(exp_tok->words[i]->word, cmd));
	if (type == OUTPUT || type == OUTPIPE || \
	type == APPEND || type == APPENDPIPE)
		return (redirect_out(exp_tok->words[i]->word, cmd, type));
	if (type == HEREDOC || type == HEREDOCPIPE)
		return (redirect_hdc(exp_tok->words[i]->hd_fd, cmd));
	return (0);
}

static int	init_cmd(t_tokens *exp_tok, t_cmd *cmd, size_t i, int j)
{
	int	type;
	int	error;

	(0 || (cmd->flag_red[IN] = 0) || (cmd->flag_red[OUT] = 0));
	(0 || (j = 0) || (cmd->err_flag = 0) || (cmd->exp_tok = exp_tok));
	cmd->err = 0;
	cmd->argc = 0;
	if (exp_tok->words[i]->type >= PIPE)
		exp_tok->words[i]->type -= PIPE;
	cmd->args = ft_calloc(sizeof(char *), dst_topipe(exp_tok, i) + 1);
	while (i < exp_tok->size)
	{
		type = exp_tok->words[i]->type;
		if (exp_tok->words[i]->type >= PIPE && j > 0)
			break ;
		else if (type > NONE)
			error = aux_init_cmd(exp_tok, cmd, i, type);
		if (type == NONE)
			cmd->args[j++] = ft_strdup(exp_tok->words[i]->word);
		if (error == 1)
			return (1);
		i++;
	}
	cmd->argc = j;
	return (0);
}

static void	free_cmd(t_cmd *cmd)
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

static void	aux_executor(t_tokens *exp_tok, t_cmd *cmd, size_t i, pid_t *pid)
{
	while (i < exp_tok->size)
	{
		if (init_cmd(exp_tok, cmd, i, 0))
			cmd->err_flag = 1;
		if (exp_tok->pipe_n != 0 && cmd->j < exp_tok->pipe_n && !cmd->err_flag)
			pipe(cmd->pipe_fd);
		if (cmd->argc && (is_blt(cmd->args[0]) || (!is_blt(cmd->args[0]) \
		&& exp_tok->pipe_n != 0)))
		{
			*pid = fork();
			if (*pid == 0)
				do_fork(exp_tok, cmd, i, cmd->j);
			close_pipe_fd(exp_tok, cmd, i);
			if (cmd->err > 0)
				return ;
		}
		else
			if (cmd->argc)
				cmd->err = check_blt(cmd, cmd->env);
		cmd->j++;
		i += dst_topipe(exp_tok, i);
		free_cmd(cmd);
	}
}

int	executor(t_tokens *exp_tok, t_env **env)
{
	size_t	i;
	t_cmd	cmd;
	pid_t	pid;

	cmd.j = 0;
	i = 0;
	cmd.env = env;
	ft_init_fd(&cmd, exp_tok);
	aux_executor(exp_tok, &cmd, i, &pid);
	wait_process(&cmd, pid, cmd.j);
	ft_close(&cmd);
	return (cmd.err);
}

///////////////////////// CHECK NO FD OPEN /////////////////////////
	// int hola = open("JAJAJA", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// printf("fd_check no fdopen:::::::::::%i\n", hola);
	// close (hola);
///////////////////////// CHECK NO FD OPEN /////////////////////////
