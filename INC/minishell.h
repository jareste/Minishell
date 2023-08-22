/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:51:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/22 16:50:32 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../INC/libft/libft.h"
# include "../INC/printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

# include "pipex.h"

# define _XOPEN_SOURCE
///borrar
# define NORM		1
# define HEREDOC	2
# define N_INTERACT	3
////
typedef struct msh_s	t_msh;
typedef struct env_s	t_env;

# define IN 0
# define OUT 1
/*  variable global */
t_msh				g_msh;
int			sig_rec;

struct msh_s
{
	char	**env;
	int		fd[2];//in0 out1
	int		err;
};

struct env_s
{
	struct env_s	*prev;
	struct env_s	*next;
	char			*key;
	char			*val;
};


typedef struct word_s
{
	char			*word;
	int				type;
	size_t			len;
	struct word_s	*next;
}				t_word;

typedef struct tokens_s
{
	t_word	*first;
	t_word	*last;
	t_word	**words;
	size_t	size;
	int		pipe_n;
	char	*str;
}				t_tokens;

typedef struct cmd_s
{
	int			pipe_fd[2];//[2]
	int			prev_pipe[2];//[2] 
	int			flag;// 0 = mid cmd 1 = start of cmd
	int			argc;
	int			err;
	char		**args;
	t_tokens	*exp_tok;
}				t_cmd;

/* pipex.c */
// int call(t_cmd *cmd);

//   ###################################################
//                    PARSER
//   ###################################################
// PARSER.C
int			parser(t_tokens *tokens);
int			break_ch(char c);

// PARSER UTILS
int			do_dots(t_tokens *tokens, char *str);
int			do_spaces(t_tokens *tokens, char *str);

// msh_words.c
t_tokens	*msh_start_words(void);
t_word		*msh_new_word(char *str, size_t len, int type);
void		print_words(t_tokens *words);
int			msh_add_word(t_tokens *words, char *str, size_t len, int type);

/* msh_words_utils.c */
int			msh_mount_matrix(t_tokens *words);
void		msh_print_tokens(t_tokens *words);
int			msh_free_tokens(t_tokens *tokens);

/* check_errors.c */
int	check_input(char *str);

//   ###################################################
//                    EXPANDER
//   ###################################################
//expander.c
int			expander(t_tokens *tokens, t_tokens *exp_tok, int err[2]);

//expand_utils.c
char		*free_join(char *ret, char *tmp);
char		*expand_dollar(t_tokens *tokens, int i, int err[2]);
char		*merge_matrix(char **matrix);

//expand_dots.c
char		*expand_dots(t_tokens *tokens, int i, size_t j);

//   ###################################################
//                    EXECUTOR
//   ###################################################
# define NONE 0
# define INPUT 1
# define OUTPUT 2
# define PIPE 3
# define INPIPE 4
# define OUTPIPE 5
# define PATH "/bin/"

int	executor(t_tokens *exp_tok, int err[2]);

//   ###################################################
//                    BUILTINS
//   ###################################################
int			blt_exit(int argc, char **argv);
int			blt_echo(int argc, char **argv);
int			blt_cd(int argc, char** argv);
int			blt_pwd(void);
int			blt_export(int argc, char **argv, t_env **env);

/* blt_env_utils.c */
t_env		*env_list(char **envs);
void		print_envs(t_env *env);
void		vervose_print_envs(t_env *env);
t_env		*free_envs(t_env **env_nodes);
t_env		*env_get_last(t_env *env);
int			ft_ichar(char *str, char c);
int			export_print(t_env *env);
char		*ft_strndup(char *str, size_t i);

int	blt_env(char **env, char *str, int to_do);

//   ###################################################
//                    SIGNALS
//   ###################################################

int	init_signals(int mode);
void	do_sigign(int signum);

#endif
