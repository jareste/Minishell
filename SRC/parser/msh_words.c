/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:42:33 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/27 00:15:08 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

t_tokens	*msh_start_words(void)
{
	t_tokens	*tokens;

	tokens = ft_calloc(1, sizeof (t_tokens));
	if (!tokens)
		return (NULL);
	tokens->words = NULL; 
	tokens->size = 0;
	return (tokens);
}

int	msh_add_word(t_tokens *tokens, char *str, size_t len, int type)
{
	t_word	*nw_word;

	if (!str)
		return (0);
	nw_word = msh_new_word(str, len, type);
	if (!nw_word)
		return (0);
	if (tokens->first == NULL)
		tokens->first = nw_word;
	else
		tokens->last->next = nw_word;
	tokens->last = nw_word;
	tokens->size += 1;
	return (1);
}

int	msh_mount_matrix(t_tokens *words)
{
	t_word	*word;
	size_t	i;

	if (!words)
		return (0);
	words->words = (t_word **) calloc(words->size + 1, sizeof(t_word *));
	if (!words->words)
		return (0);
	word = words->first;
	i = 0;
	while (word)
	{
		words->words[i] = word;
		word = word->next;
		i++;
	}
	return (1);
}

t_word	*msh_new_word(char *str, size_t len, int type)
{
	t_word	*word;

	word = ft_calloc(1, sizeof (t_word));
	if (!word)
		return (NULL);
	word->word = calloc(len + 1, sizeof (char));
	if (!word->word)
	{
		free(word);
		return (NULL);
	}
	word->len = len;
	word->type = type;
	word->next = NULL;
	word->word[len] = '\0';
	while (len-- > 0)
		word->word[len] = str[len];
	return (word);
}
