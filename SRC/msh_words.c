#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"


t_tokens	 *msh_start_words(void)
{
	t_tokens *words;

	words = calloc(1, sizeof (t_tokens)); // forbiden function
	if (!words)
		return (NULL);
	words->words = NULL; 
	words->size = 0;
	return (words);
}

int	msh_add_word(t_tokens *words, char *orig_word, size_t len, int type)
{
	t_word *nw_word;

	if (!orig_word)
		return (0);
	nw_word = msh_new_word(orig_word, len, type);
	if (!nw_word) // mem leak
		return (0);
	if (words->first == NULL)
		words->first = nw_word;
	else
		words->last->next = nw_word;
	words->last = nw_word;
	words->size += 1;
	return (1);
}

int msh_mount_matrix(t_tokens *words)
{
	t_word	*word;
	size_t		i;

	if (!words)
		return (0);
	words->words = (t_word **) calloc(words->size + 1, sizeof(t_word *));
	if (!words->words)
		return (0);
	word = words->first;
	i = 0;
	while(word)
	{
		words->words[i] = word;
		word = word->next;
		i++;
	}
	return (1);
}
t_word *msh_new_word(char *orig_word, size_t len, int type)
{
	t_word	*word;

	word = calloc(1, sizeof (t_word)); // forbiden function
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
		word->word[len] = orig_word[len];
	return word;
}


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
