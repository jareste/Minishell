/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:16:56 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/18 13:10:48 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

static int	path_list(char ***path, char *command, char **envp)
{
	char	*path_str;

	if (!command || !envp || !command[0])
		return (0);
	path_str = get_env(envp, "PATH");
	if (path_str == NULL)
	{
		*path = ft_split(DEF_PATH, ':');
		return (*path != NULL);
	}
	else if (envp[0] && !path_str[1])
		return (0);
	else
	{
		*path = ft_split(path_str + 1, ':');
		return (*path != NULL);
	}
	*path = ft_split(DEF_PATH, ':');
	if (!*path)
		return (0);
	return (1);
}

int	initial_tests(char **result, char *command)
{
	if (command[0] == '.' && command[1] == 47)
	{
		while (command[0] == '.' && command[1] == 47)
			command += 2;
		if (!access(command, X_OK))
			*result = ft_strdup(command);
		else 
			*result = NULL;
		return (1);
	}
	if (command[0] == '/' && !access(command, X_OK))
	{
		*result = ft_strdup(command);
		return (1);
	}
	else if (!access(command, X_OK) && ft_strchr(command, '/'))
	{
		*result = ft_strdup(command);
		return (1);
	}
	return (0);
}

char	*get_path(char *command, char **envp)
{
	size_t	i;
	int		err;
	char	**path;
	char	*exec_str;
	char	*result;

	if (initial_tests(&result, command))
		return (result);
	path = NULL;
	if (!path_list(&path, command, envp))
		return (NULL);
	err = 0;
	i = -1;
	while (path[++i])
	{
		exec_str = psw_join_paths(path[i], command);
		if (!access(exec_str, X_OK))
		{
			free_list(path);
			return (exec_str);
		}
		update_err_and_file_err(&err, errno);
		free(exec_str);
	}
	return (NULL);
}

char	*psw_join_paths(char *path1, char *path2)
{
	int		len;
	char	*result;
	char	slash_needed;

	len = ft_strlen(path1);
	slash_needed = !(path1[len - 1] == '/');
	len += slash_needed;
	len += ft_strlen(path2);
	len++;
	result = malloc(len);
	if (!result)
		return (NULL);
	result[0] = '\0';
	ft_strlcat(result, path1, len);
	if (slash_needed)
		ft_strlcat(result, "/", len);
	ft_strlcat(result, path2, len);
	return (result);
}

int	ppx_patherr(char **oargv, char **envp, char *path, char **argv)
{
	char	*err_program_str;
	int		exit_val;

	exit_val = 127;
	err_program_str = get_env(envp, "SHELL");
	if (!err_program_str)
		err_program_str = oargv[0];
	if (!err_program_str)
		return (exit_val);
	err_program_str = ft_strrchr(err_program_str, '/') + 1;
	ft_printf(2, "%s: ", err_program_str);
	if (argv[0][0] == '.' && argv[0][1] == '/')
	{
		ft_printf(2, "%s: No such file or directory\n", argv[0]);
		if (access(path, F_OK))
			exit_val = 126;
	}
	else
		ft_printf(2, "%s: command not found\n", argv[0]);
	return (exit_val);
}
