/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:33:05 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 19:29:13 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	call(t_cmd *cmd, t_env **env)
{
	char	**paths;
	char	*path_test;
	int		i;
	int		ret;

	if (!ft_getenv(*env, "PATH"))
		return (1);
	paths = ft_split(ft_getenv(*env, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path_test = ft_strjoin(ft_strjoin(paths[i], "/"), cmd->args[0]);
		ret = execve(path_test, cmd->args, NULL);
		free(path_test);
		if (ret == 0)
		{
			free(paths);
			return (0);
		}
		i++;
	}
	free(paths);
	return (1);
}

static int	call_wo_path(t_cmd *cmd)
{
	if (execve(cmd->args[0], cmd->args, NULL) == -1)
		return (1);
	return (0);
}

int	exe_cmd(t_cmd *cmd, t_env **env)
{
	if (check_blt(cmd, env) == 0)
		return (0);
	else if (call(cmd, env) == 0)
		return (0);
	else if (call_wo_path(cmd) == 0)
		return (0);
	else
		ft_printf(2, "%s: command not found\n", cmd->args[0]);
	return (127);
}

int	dst_topipe(t_tokens *exp_tok, size_t i)
{
	int	j;

	j = 0;
	while (i < exp_tok->size)
	{
		if (exp_tok->words[i]->type < PIPE)
			j++;
		else if (exp_tok->words[i]->type >= PIPE)
			break ;
		i++;
	}
	return (j);
}
