/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:24:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 21:39:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

static int	start(t_tokens *tokens, t_tokens *exp_tok, t_env **env, int err[2])
{
	err[0] = parser(tokens);
	if (err[0] == 0)
	{
		err[0] = expander(tokens, exp_tok, err);
		if (err[0] == 0)
			err[0] = executor(exp_tok, env);
	}
	return (err[0]);
}

static int	aux_rl_fail(t_tokens *tokens, t_tokens *exp_tok)
{
	if (isatty(STDIN_FILENO))
		ft_printf(2, "exit\n");
	(1 && (msh_free_tokens(tokens)) && (msh_free_tokens(exp_tok)));
	return (0);
}

static void	check_global(int err[2])
{
	if (g_sig_rec > 0)
	{
		err[1] = g_sig_rec;
		g_sig_rec = 0;
	}
}

int	main(int argc, char **argv, char *envp[])
{
	t_tokens	*tokens;
	t_tokens	*exp_tok;
	t_env		*env;
	int			err[2];

	(0 || (argc = 0) || (argv = 0) || (err[1] = 0) || (err[0] = 0));
	env = env_list(envp);
	g_sig_rec = 0;
	while (1)
	{
		tokens = msh_start_words(&env);
		exp_tok = msh_start_words(&env);
		init_signals(NORM);
		do_sigign(SIGQUIT);
		tokens->str = readline("🎷🦄miniHell> ");
		do_sigign(SIGINT);
		if (!tokens->str)
			return (aux_rl_fail(tokens, exp_tok));
		err[1] = start(tokens, exp_tok, &env, err);
		msh_free_tokens(tokens);
		msh_free_tokens(exp_tok);
		check_global(err);
	}
	return (0);
}
// msh_print_tokens(tokens);
// printf("#######tokens ended######\n\n"); //s
// msh_print_tokens(exp_tok);
// printf("#######exp ended######\n\n");  //ss
// printf("#######exe ended######\n\n");  //ss