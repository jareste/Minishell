
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../INC/libft/libft.h"
# include "../INC/printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_word
{
	char	*word;
	int		dot;
}		t_word;

typedef struct s_tokens
{
	t_word	*words;
	char	*str;
}		t_tokens;

void	parser(char	*str, t_tokens	*tokens);
// typedef struct word_s{
// 	char	*word;
// 	int		type;
// 	size_t	len;
// 	struct word_s	*next;

// } t_word;

// typedef struct words_s{
// 	t_word	*first;
// 	t_word	*last;
// 	t_word	**words;
// } t_words;

// void msh_print_word(char *format_str, t_word word);
// void print_words(t_words *words);
// int	msh_add_word(t_words *words, char *orig_word, size_t len, int type);
// t_word *msh_new_word(char *orig_word, size_t len, int type);
// void msh_start_words(t_words *words);

#endif
