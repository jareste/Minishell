/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/16 10:37:30 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	redirect_in(char *str, t_cmd *cmd)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		// printf("openedIN:::%s::::::%i:::fd_in::::%i\n", str, fd, cmd->fd_in);
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		cmd->fd_in = fd;
	}
	return (0);
}

int	redirect_out(char *str, t_cmd *cmd)
{
	int	fd;

	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > 2)
	{
		// printf("openedOUT:::%s::::::%i:::::fd_out:::%i\n", str, fd, cmd->fd_out);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd->fd_out = fd;
		// if (close(fd) == -1)
			// printf("badclose\n");
	}
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

	cmd->fd_in = 0; // 2fds, 0 == old, 1 == NEW
	cmd->fd_out = 1; // 2fds, 0 == old, 1 == NEW
	cmd->exp_tok = exp_tok;
	if (exp_tok->words[i]->type >= 3)
		exp_tok->words[i]->type -= 3;
	cmd->args = ft_calloc(sizeof(char *), dst_topipe(exp_tok, i));
	j = 0;
	// printf("dst_topipe::::::::%i\n", dst_topipe(exp_tok, i));
	while (i < exp_tok->size)//esto no sirve (creo)
	{
		// printf("type::::::::%i  %i\n", exp_tok->words[i]->type, PIPE);
		if (exp_tok->words[i]->type >= PIPE && j > 0)
			break ;
		else if (exp_tok->words[i]->type == INPUT || exp_tok->words[i]->type == INPIPE)
			redirect_in(exp_tok->words[i]->word, cmd);
		else if (exp_tok->words[i]->type == OUTPUT || exp_tok->words[i]->type == OUTPIPE)
			redirect_out(exp_tok->words[i]->word, cmd);
		else
		{
			cmd->args[j] = ft_strdup(exp_tok->words[i]->word);
			j++;
		}
		i++;
	}
	// printf("j:::::::::::%i\n", j);
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


int	executor(t_tokens *exp_tok)
{
	size_t	i;
	int		flag;
	t_cmd	cmd;
	pid_t	pid;
	int		status;

	i = 0;
	flag = 1;
	while (i < exp_tok->size)
	{
		init_cmd(exp_tok, &cmd, i);
		if (ft_strncmp("echo", cmd.args[0], ft_strlen(cmd.args[0])) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd.fd_out != 1)
					dup2(cmd.fd_out, STDOUT_FILENO);
				blt_echo(cmd.argc, cmd.args);
				exit(1);
			}
		}
		waitpid(pid, &status, 0);
		i += dst_topipe(exp_tok, i);
		// printf("mainbucle:::::::::%zu, %zu\n", i, exp_tok->size);
		// free_cmd(&cmd);
		// exit(1);
	}


 	return (0);
}


//FUNCIONA EJECUTA CAT
/*
char *args[4];
args[0] = "cat";
args[1] = "tst";
args[2] = NULL;
args[3] = NULL;

int output_fd = open("afd", O_WRONLY | O_CREAT | O_TRUNC, 0644);

 pid_t pid = fork();
        // printf("pid:%i\n", pid);

    if (pid == 0) {  // Proceso hijo
        // Redirigir la salida estándar al archivo
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd); // Cerrar el descriptor de archivo
        execve("/bin/cat", args, NULL); // Usar la ruta completa de "cat"
        return 1;
    }
*/