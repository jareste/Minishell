/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:37:48 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/02 19:59:06 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

//he convertit les func no critiques a static ja que se suposa que sols les cridarem desde aqui, doncs haurien de ser static, encara que crec
//que son temporals.
 
static void	msh_print_word(char *format_str, t_word word)
{
	if (!format_str)
		printf("{%d}%s<", word.type, word.word); //forbidden function
	else
		printf(format_str, word.type, word.word); //forbidden function
}

static void	msh_print_words(t_words *words)
{
	t_word *word;
	
	word = words->first;
	while (word)
	{
		msh_print_word("%d: >>%s<<\n", *word); //forbiden function	
		word = word->next;
	}
}

void msh_start_words(t_words *words)// he modificat aquesta funció, ja que aixi podem enviar desde el main la direccio a totes
{
	// t_words *words;

	words = ft_calloc(1, sizeof (t_words)); // forbiden function // he posat calloc de libft
	if (!words)
		return ;
	words->words = NULL; 
	// return (words);
}

int	msh_add_word(t_words *words, char *orig_word, size_t len, int type)
{
	t_word *nw_word;

	nw_word = msh_new_word(orig_word, len, type);
	if (!nw_word) // mem leak
		return (0);
	if (words->words == 0)
		words->first = nw_word;
	else
		words->last->next = nw_word;
	words->last = nw_word;
	return (1);
}

t_word *msh_new_word(char *orig_word, size_t len, int type)
{
	t_word	*word;

	word = ft_calloc(1, sizeof (t_word)); // forbiden function//he posat calloc libft
	if (!word)
		return (NULL);
	word->word = calloc(len + 1, sizeof (char));
	if (!word->word)
	{
		free(word);
		return (NULL);
	}
	word->word[len] = '\0';
	while (--len >= 0)
		word->word[len] = orig_word[len];
	word->len = len;
	word->type = type;
	word->next = NULL;
	return word;
}

int main(void)
{
	t_words words;

	msh_start_words(&words);
	msh_add_word(&words, "hellowwwwwwwwwww", 7, 1); //podem cridar aquesta funcio desde start words?
	msh_print_words(&words);
	printf("----------\n");
	msh_add_word(&words, "wakaaaaaaaaaaa", 4, 1);
	msh_print_words(&words);
	printf("----------\n");
	msh_add_word(&words, "byeeeeeeeeeee", 4, 1);
	msh_print_words(&words);
	printf("----------\n");
	while (words.first)
		free(words.first);
	return (0);
}
