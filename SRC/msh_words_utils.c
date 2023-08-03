#include "minishell.h"

void	msh_print_word(char *format_str, t_word word)
{
	if (!format_str)
		printf("{%d}%s<", word.type, word.word);
	else
		printf(format_str, word.type, word.word);
}

void	msh_print_words_by_list(t_tokens *words)
{
	t_word *word;
	
	word = words->first;
	while (word)
	{
		msh_print_word("%d: >>%s<<\n", *word);	
		word = word->next;
	}
}

void	msh_print_words(t_tokens *words)
{
	size_t i;

	i = 0;
	while (words->words[i])
	{
		msh_print_word("%d: >>%s<<\n", *words->words[i]);	
		i += 1;
	}
}

int msh_free_words(t_tokens *words)
{
	t_word *word;
	t_word *aux;

	word = words->first;
	while (word)
	{
		aux = word->next;
		free(word->word);
		free(word);
		word = aux;
	}
	if (words->words)
		free(words->words);
	free(words);
	return (1);
}
