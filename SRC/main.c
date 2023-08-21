/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:24:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/21 07:47:32 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

static int	start(t_tokens *tokens, t_tokens *exp_tok)
{
	g_msh.err = parser(tokens);
	if (g_msh.err == 0)
	{
		msh_print_tokens(tokens);
		printf("#######tokens ended######\n\n"); //s
		g_msh.err = expander(tokens, exp_tok);
		msh_print_tokens(exp_tok);
		printf("#######exp ended######\n\n");  //ss
		g_msh.err = executor(exp_tok);
		// printf("#######exe ended######\n\n");  //ss
	}
	return (g_msh.err);
}

int	main(int argc, char **argv, char *env[])
{
	t_tokens	*tokens;
	t_tokens	*exp_tok;

	(0 || (argc = 0) || (argv = 0));
	(void)env;//we should start env on global var
	while (1)
	{
		init_signals(NORM);
		do_sigign(SIGQUIT);
		(1 && (tokens = msh_start_words()) && (exp_tok = msh_start_words()));
		tokens->str = readline("🎷🦄miniHell> ");
		do_sigign(SIGINT);
		if (!tokens->str)
		{
			if (isatty(STDIN_FILENO))
				ft_printf(2, "exit\n");
			(1 && (msh_free_tokens(tokens)) && (msh_free_tokens(exp_tok)));
			return (0);
		}
		start(tokens, exp_tok);
		(1 && (msh_free_tokens(tokens)) && (msh_free_tokens(exp_tok)));
		if (g_msh.err == -2) // sobra
			break ;//sobra
	}
	return (0);
}


	//#######################for geting env#################
	 // char **ptr_env;
	 // ptr_env = env;
	 // while (*ptr_env)
	 // {
	 // 	printf("%s\n", *ptr_env);
	 // 	ptr_env++;
	 // }
	//#######################for geting env#################
	
	// blt_env(env);
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
