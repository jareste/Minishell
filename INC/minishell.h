/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:51:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/06 13:29:42 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct word_s{
	char			*word;
	int				type;
	size_t			len;
	struct word_s	*next;

}				t_word;

typedef struct tokens_s{
	t_word	*first;
	t_word	*last;
	t_word	**words;
	size_t	size;
	char	*str;
}				t_tokens;

// PARSER.C
int			parser(t_tokens *tokens);
int			break_ch(char c);

// PARSER UTILS
int			do_dots(t_tokens *tokens, char *str);
int			do_spaces(t_tokens *tokens, char *str);
// int			do_break(t_tokens *tokens, char *str);

// msh_words.c
t_tokens	*msh_start_words(void);
t_word		*msh_new_word(char *str, size_t len, int type);
void		print_words(t_tokens *words);
int			msh_add_word(t_tokens *words, char *str, size_t len, int type);

/* msh_words_utils.c */
int			msh_mount_matrix(t_tokens *words);
void		msh_print_tokens(t_tokens *words);
int			msh_free_tokens(t_tokens *tokens);

//expander.c
int			expander(t_tokens *tokens);

#endif
