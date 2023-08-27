/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_words_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:42:48 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/27 00:15:32 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static void	msh_print_word(char *format_str, t_word word)
{
	if (!format_str)
		printf("{%d}%s<", word.type, word.word);
	else
		printf(format_str, word.type, word.word);
}

void	msh_print_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (tokens->words[i])
	{
		msh_print_word("%d: >>%s<<\n", *tokens->words[i]);
		i += 1;
	}
}

int	msh_free_tokens(t_tokens *tokens)
{
	t_word	*word;
	t_word	*aux;

	word = tokens->first;
	while (word)
	{
		aux = word->next;
		free(word->word);
		free(word);
		word = aux;
	}
	if (tokens->words)
		free(tokens->words);
	if (tokens->str)
		free(tokens->str);
	free(tokens);
	return (1);
}
