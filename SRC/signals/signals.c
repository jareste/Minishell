/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:35:28 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/22 18:12:49 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

void	ninter_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		printf("\n");
		sig_rec = 130;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		sig_rec = 131;
	}
	return ;
}

void	do_sigign(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit (1);
}

void	norm_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		sig_rec = 1;
	}
	return ;
}

int	init_signals(int mode)
{
	struct sigaction	signal;

	// sig_rec = 0;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (mode == NORM)
		signal.sa_sigaction = norm_handler;
	else if (mode == N_INTERACT)
		signal.sa_sigaction = ninter_handler;
	// else if (mode == HEREDOC)
	// 	signal.sa_sigaction = heredoc_handler;
	// printf("%i,\n", mode);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	return (0);
}