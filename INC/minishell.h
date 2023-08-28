/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:51:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 19:21:02 by jareste-         ###   ########.fr       */
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

# define _XOPEN_SOURCE
///borrar
# define NORM		1
// # define HEREDOC	2
# define N_INTERACT	3
////
// typedef struct msh_s	t_msh;
// typedef struct env_s	t_env;

# define IN 0
# define OUT 1
/*  variable global */
int			g_sig_rec;

typedef struct env_s
{
	struct env_s	*prev;
	struct env_s	*next;
	char			*key;
	char			*val;
}				t_env;

typedef struct word_s
{
	char			*word;
	int				type;
	size_t			len;
	int				hd_fd;
	struct word_s	*next;
}				t_word;

typedef struct tokens_s
{
	t_word	*first;
	t_word	*last;
	t_word	**words;
	size_t	size;
	int		pipe_n;
	int		error;
	char	*str;
	t_env	**env;
}				t_tokens;

typedef struct aux_exp_s
{
	size_t		i;
	size_t		j;
	int			len;
	char		**str;
	char		*src;
	int			type;
}				t_aux_exp;

typedef struct cmd_s
{
	int			init_fd[2];
	int			pipe_fd[2];
	int			prev_pipe[2];
	int			flag_red[2];
	int			flag;
	int			argc;
	int			err;
	int			err_flag;
	int			hdc_flag;
	int			j;
	int			*hdc_aux;
	char		**args;
	t_tokens	*exp_tok;
	t_env		**env;
}				t_cmd;

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
t_tokens	*msh_start_words(t_env **env);
t_word		*msh_new_word(char *str, size_t len, int type);
void		print_words(t_tokens *words);
int			msh_add_word(t_tokens *words, char *str, size_t len, int type);

/* msh_words_utils.c */
int			msh_mount_matrix(t_tokens *words);
void		msh_print_tokens(t_tokens *words);
int			msh_free_tokens(t_tokens *tokens);
char		**env_matrix(t_env *_envs);
void		print_matrix(char **matrix);
char		**free_matrix(char **matrix);

/* check_errors.c */
int			check_input(char *str);

//   ###################################################
//                    EXPANDER
//   ###################################################
//expander.c
int			expander(t_tokens *tokens, t_tokens *exp_tok, int err[2]);

//expand_utils.c
char		*free_join(char *ret, char *tmp);
char		*expand_dollar(t_tokens *tokens, int i, int err[2]);
char		*merge_matrix(char **matrix, int len);
int			dst_doll_brk(char *str, int i);

//expand_utils2.c
int			exp_type(t_tokens *tokens, int i);
int			count_pipes(t_tokens *tokens);
void		new_tokens(t_tokens *exp_tok, char *str, int type);

//expand_dots.c
char		*expand_dots(t_tokens *tokens, int i, size_t j, char *ret);

//   ###################################################
//                    EXECUTOR
//   ###################################################
# define NONE 0
# define INPUT 1
# define OUTPUT 2
# define HEREDOC 3
# define APPEND 4
# define PIPE 5
# define INPIPE 6
# define OUTPIPE 7
# define HEREDOCPIPE 8
# define APPENDPIPE 9
# define PATH "/bin/"

//executor.c
int			executor(t_tokens *exp_tok, t_env **env);

//exe_redirects.c
int			redirect_in(char *str, t_cmd *cmd);
int			redirect_out(char *str, t_cmd *cmd, int type);
int			redirect_hdc(int fd, t_cmd *cmd);

//heredoc.c
int			do_hdc(t_tokens *exp_tok);

//blt_checks.c
int			check_blt(t_cmd *cmd, t_env **env);
int			is_blt(char *str);

//exe_cmd.c
int			exe_cmd(t_cmd *cmd, t_env **env);
int			dst_topipe(t_tokens *exp_tok, size_t i);

//executor_utils.c
void		ft_close(t_cmd *cmd);
void		ft_init_fd(t_cmd *cmd, t_tokens *exp_tok);
void		do_fork(t_tokens *exp_tok, t_cmd *cmd, int i, int j);
void		wait_process(t_cmd *cmd, pid_t pid, int j);
void		close_pipe_fd(t_tokens *exp_tok, t_cmd *cmd, size_t i);

//   ###################################################
//                    BUILTINS
//   ###################################################
int			blt_exit(int argc, char **argv);
int			blt_echo(int argc, char **argv);
int			blt_cd(int argc, char **argv, t_env **env);
int			blt_pwd(void);
int			blt_export(int argc, char **argv, t_env **env);

char *ft_getenv(t_env *_env, char *target);
/* blt_env_utils.c */
t_env		*env_list(char **envs);
void		print_envs(t_env *env);
void		vervose_print_envs(t_env *env);
t_env		*free_envs(t_env **env_nodes);
t_env		*env_get_last(t_env *env);
int			ft_ichar(char *str, char c);
int			export_print(t_env *env);
char		*ft_strndup(char *str, size_t i);

int	blt_envv(int argc, char **argv, t_env **envp);
int	blt_unset(char **argv, t_env **_env);
int export_add(char **argv, t_env **_env);
char **tokens_to_matrix(t_tokens *tokens);
t_env	*free_env(t_env *env);

//   ###################################################
//                    SIGNALS
//   ###################################################

int			init_signals(int mode);
void		do_sigign(int signum);

//##################
void		print_envs(t_env *env);
t_env		*env_list(char **envs);
int			blt_export(int argc, char **argv, t_env **env);

#endif
