/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:18:12 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/18 13:40:47 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "minishell.h"

# define DEF_PATH "/usr/bin:./assets"
//# define DEF_PATH "./assets"
# include <stdio.h>//printf


/* ppx_utils.c */
int		free_list(char **list);
void	twk_log(char *str);
char	*get_env(char **envp, char *var);
void	print_list(char **list);
int		close_fds(int *fd1, int *fd2, int *fd3, int *fd4);

/* ppx_wend */ //TODO DELTE
size_t	ppx_findwend(char *args, size_t *start, size_t *end);
void	ppx_wnd_backslash(char *args_cpy, size_t *i, size_t *end);
int		ppx_wnd_1quote(char *args_cpy, size_t *i, size_t *end);
int		ppx_wnd_2quotes(char *args_cpy, size_t *i, size_t *end);
void	ppx_wnd_putnull(char *args_cpy, size_t *i, size_t *end);

/* ppx_get_path.c */
/* static int	path_list(char ***path, char *command, char **envp); */
int		initial_tests(char **result, char *command);
char	*get_path(char *command, char **envp);
char	*psw_join_paths(char *path1, char *path2);
int		ppx_patherr(char **oargv, char **envp, char *path, char **argv);

/* ppx_spliter.c */ // TODO DELETE
void	ppx_print_matrix(char **mtrx);
char	**ppx_free_matrix(char **mtrx);
char	**ppx_split(char *args);
char	**ppx_ptarg(char **result, char *args_cpy, size_t start);

/* ppx_utils.c */
int		fdf_init_main_variables(int *ret, pid_t pids[2], int fds[2]);
int		check_arg_number(int nargs);
void	update_err_and_file_err(int *err, int err_no);
#endif
