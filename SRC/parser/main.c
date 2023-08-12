/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:24:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 00:18:38 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
/*
int main(void)
{
	t_tokens *words;

	words = msh_start_words();
	printf("-----hellow-----\n");
	msh_add_word(words, "hellowwwwwwwwwww", 7, 1);
	printf("added word\n");
	msh_print_words_by_list(words);
	printf("-----waka-----\n");
	msh_add_word(words, "wakaaaaaaaaaaa", 4, 1);
	msh_print_words_by_list(words);
	printf("-----NULL-----\n");
	msh_add_word(words, NULL, 4, 1);
	msh_print_words_by_list(words);
	printf("-----len0-----\n");
	msh_add_word(words, "", 4, 1);
	msh_print_words_by_list(words);
	printf("-----bye-----\n");
	msh_add_word(words, "byeeeeeeeeeee", 4, 1);
	msh_print_words_by_list(words);
	printf("-----Mounting Matrix-----\n");
	msh_mount_matrix(words);
	msh_print_words(words);
	printf("----------\n");
	msh_free_words(words);
}*/

int	main(int argc, char **argv, char *env[])
{
	t_tokens	*tokens;
	t_tokens	*exp_tok;

	argc = 0;
	argv = 0;
	(void) env;
	while (1)
	{
		tokens = msh_start_words();
		exp_tok = msh_start_words();
		int tmp_exit = parser(tokens);
		if (tmp_exit == 0)
		{
			msh_print_tokens(tokens);
			printf("#######tokens ended######\n\n"); //s
			expander(tokens, exp_tok);
			msh_print_tokens(exp_tok);
			printf("#######exp ended######\n\n");  //ss
		}
		msh_free_tokens(tokens);
		msh_free_tokens(exp_tok);
		if (tmp_exit == -2)
			break;
	}
	return (0);
}
