/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:24:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/06 02:19:01 by jareste-         ###   ########.fr       */
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

	argc = 0;
	argv = 0;
	env = 0;
	while (1)
	{
		tokens = msh_start_words();
		parser(tokens);

		add_history(tokens->str);
		expander(tokens);
	msh_print_tokens(tokens);
	msh_free_tokens(tokens);
	}
	return (0);
}
