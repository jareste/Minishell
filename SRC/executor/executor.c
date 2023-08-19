/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:45:36 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/19 13:01:53 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	redirect_in(char *str, t_cmd *cmd)
{
	int	fd;

	(void)cmd;
	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		// if (cmd->fd_in[0] != 0)
		// 	close(cmd->fd_in[0]);
        dup2(fd, STDIN_FILENO);
        // cmd->fd_flag[0] = 1;
	}
	return (0);
}

int	redirect_out(char *str, t_cmd *cmd)
{
	int	fd;
	// int	old_fd;

	(void)cmd;
	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// old_fd = 2; // No es fa servir nomes s'asigna? //si
	if (fd > 2) // en principi sempre sera major que 2, ja que 2 es stderr //si, hauria de
	{
		// printf("...........fdin..........:%i, fd::::::::::%i.\n", cmd->fd_in[1], fd);
		// old_fd = cmd->fd_in[1]; // No es fa servir nomes s'asigna?
		// if (cmd->fd_in[1] != 1)
			// close(cmd->fd_in[1]);
		//dup2(cmd->fd_in[1], fd);
		dup2(fd, STDOUT_FILENO);
        // if (old_fd > 2)
        // 	close(old_fd);
        // cmd->fd_flag[1] = 1;
		// printf("AFTER..............fdin..........:%i, fd::::::::::%i.\n", cmd->fd_in[1], old_fd);
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
	int	type;
	// TODO els fds potser es tindiren que inicialitzar a -1 per saber si realment fan refrencia a un fd
	// cmd->fd_in[0] = 0; // 2fds, 0 == old, 1 == NEW
	// cmd->fd_in[1] = 1; // 2fds, 0 == old, 1 == NEW
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
			redirect_in(exp_tok->words[i]->word, cmd);
		else if (type == OUTPUT || type == OUTPIPE)
			redirect_out(exp_tok->words[i]->word, cmd);
		else
			cmd->args[j++] = ft_strdup(exp_tok->words[i]->word);
		i++;
	}
	cmd->argc = j;
	cmd->aux_cd = 0;
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
	if (ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		return (blt_echo(cmd->argc, cmd->args));
	else if (ft_strncmp("cd", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		printf("cd\n");//return (blt_cd(cmd->argc, cmd->args));
	else if (ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		return(blt_pwd());
	else if (ft_strncmp("export", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		printf("export\n");//blt_export;
	else if (ft_strncmp("unset", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		printf("unset\n");//blt_unset;
	else if (ft_strncmp("env", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		printf("env\n");//blt_env;
	else if (ft_strncmp("exit", cmd->args[0], ft_strlen(cmd->args[0])) == 0)
		printf("exit\n");//blt_exit;
	return (1);
	//if error return 1;
}


int	call(t_cmd *cmd)
{
	char	*pth;

	pth = ft_strjoin(PATH, cmd->args[0]);
	// printf("::::::::%s\n", pth);
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
		printf("CHECK_BLT\n");//ss
	else if (call(cmd) == 0)
		printf("CALL\n'");//ss
	else if (call_wo_path(cmd) == 0)
		printf("CALLWO\n");//s
	else
		printf("error\n");//s
	return (0);
}

int	executor(t_tokens *exp_tok, char **envp)
{
	size_t	i;
	t_cmd	cmd;
	pid_t	pid;
	int		status;
	int		j;
	int		fdout;
	int		fdin;

	j = 0;
	i = 0;
	cmd.fd_in[0] = 0; // 2fds, 0 == old, 1 == NEW
	cmd.fd_in[1] = 1;
	cmd.env = envp;
	fdout = dup(STDOUT_FILENO);
	fdin = dup(STDIN_FILENO);
	// printf("pipes:::::::::%i\n", exp_tok->pipe_n);
	while (i < exp_tok->size)
	{
		// printf("i::::%zu, exptok:::::::%zu, pipe_n:::::%i, j::::::%i\n", i, exp_tok->size -1, exp_tok->pipe_n, j);
		if (exp_tok->pipe_n != 0 && j < exp_tok->pipe_n) //i < exp_tok->size - 1)
			pipe(cmd.fd_in);
		init_cmd(exp_tok, &cmd, i);
		pid = fork();
		if (!pid) // es pot gestinar dins del call per tal destalviar linies
			//si, tot aixo va dins una funcio, pero aixo ja ho fare quan sigui validat.
		{
			if (i > 0 && exp_tok->pipe_n != 0)
			{
				close(cmd.prev_pipe[1]); // TODO no se si es possible que tanci el stdin en cas de que no s'hagi innicialitzat
				dup2(cmd.prev_pipe[0], STDIN_FILENO);
				close(cmd.prev_pipe[0]);
			}
			if (i < exp_tok->size - 1 && exp_tok->pipe_n != 0)
			{
				close(cmd.fd_in[0]); // TODO no se si es possible que tanci el stdin en cas de que no s'hagi innicialitzat
				dup2(cmd.fd_in[1], STDOUT_FILENO);
				close(cmd.fd_in[1]);
			}
			exit(exe_cmd(&cmd));
		}
		// printf("aux:::::::::%i, pipe::::::::::%i\n",cmd.aux_cd ,exp_tok->pipe_n);
		if (i > 0)
		{
			close(cmd.prev_pipe[0]);
			close(cmd.prev_pipe[1]);
		}
		if (i < exp_tok->size - 1)
		{
			cmd.prev_pipe[0] = cmd.fd_in[0];
			cmd.prev_pipe[1] = cmd.fd_in[1];
		}
		j++;
		i += dst_topipe(exp_tok, i);
		free_cmd(&cmd);
	}
	if (exp_tok->size == 1)
		waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		i++;
	dup2(fdout, STDOUT_FILENO);
	dup2(fdin, STDIN_FILENO);
	close(fdout);
	close(fdin);
	int hola = open("JAJAJA", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("fd:::::::::::%i\n", hola);
	close (hola);
	return (0);
}









// OLD EXECUTOR
	// size_t	i;
	// int		flag;
	// t_cmd	cmd;
	// pid_t	pid;
	// int		status;

	// // pid = ft_calloc(exp_tok->pipe_n + 1, sizeof(pid_t));
	// if (exp_tok->pipe_n != 0)
	// 	pipe(cmd.fd_in);
	// // printf("IN:%i\nOUT:%i\n", cmd.fd_in[0], cmd.fd_in[1]);
	// i = 0;
	// flag = 1;
	// printf("pipes:::::::::%i\n", exp_tok->pipe_n);
	// while (i < exp_tok->size)
	// {
	// 	init_cmd(exp_tok, &cmd, i);
	// 	pid = fork();
	// 	if (!pid) 
	// 	{
	// 		if (exp_tok->pipe_n != 0)
	// 		{
	// 			if (i > 0)
	// 			{
	// 				close(cmd.fd_in[1]);
	// 				dup2(cmd.fd_in[0], STDIN_FILENO);
	// 				close(cmd.fd_in[0]);
	// 			}
	// 			if (i < exp_tok->size - 1)
	// 			{
	// 				close(cmd.fd_in[0]);
	// 				dup2(cmd.fd_in[1], STDOUT_FILENO);
	// 				close(cmd.fd_in[1]);
	// 			}
	// 		}
	// 		exit(exe_cmd(&cmd));
	// 	}
	// 	if (i > 0)
	// 	{
	// 		close(cmd.fd_in[1]);
	// 		close(cmd.fd_in[0]);
	// 	}
	// 	if (i == exp_tok->size - 1)
	// 		break ;
	// 	i += dst_topipe(exp_tok, i);
	// 	free_cmd(&cmd);
	// }
	// if (exp_tok->size == 1)
	// 	waitpid(pid, &status, 0);
	// while (wait(NULL) > 0)
	// 	i++;
	// return (0);


/*   OLD EXECUTOR:::::::
		init_cmd(exp_tok, &cmd, i);
	
		pid = fork();
		if (!pid)
		{
		   if (i > 0) {
                close(cmd.fd_in[1]);  // Cerrar el descriptor de escritura de la tubería
                dup2(cmd.fd_in[0], STDIN_FILENO);  // Redirigir la entrada estándar al descriptor de lectura de la tubería
                close(cmd.fd_in[0]);  // Cerrar el descriptor de lectura no utilizado
            }
            
            // Redirigir stdout al descriptor de escritura de la tubería
            close(cmd.fd_in[0]);
            dup2(cmd.fd_in[1], STDOUT_FILENO);
            close(cmd.fd_in[1]);
            
            exit(exe_cmd(&cmd));




	
		}
	if (exp_tok->size == 1) {
    waitpid(pid, &status, 0);
}

// Esperar a que se completen todos los comandos
	int k = 0;
	while (wait(NULL) > 0)
		k++;

		i += dst_topipe(exp_tok, i);
		free_cmd(&cmd);
	}
 	return (0);
}*/

	//estaba despues del exit.
	// 	close(cmd.fd_in[0]);
		// 	dup2(cmd.fd_in[1], STDOUT_FILENO);
		// 	close(cmd.fd_in[1]);			
		// 	exit(exe_cmd(&cmd));
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
