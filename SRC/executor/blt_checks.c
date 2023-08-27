/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:33:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/27 09:28:00 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	check_blt(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 0;
	cmd->flag_red[IN] = 0;
	cmd->flag_red[OUT] = 0;
	while (cmd->args[0][i])
		ft_tolower(cmd->args[0][i++]);
	if (ft_strncmp("echo", cmd->args[0], ft_strlen("echo") + 1) == 0)
		return (blt_echo(cmd->argc, cmd->args));
	else if (ft_strncmp("cd", cmd->args[0], ft_strlen("cd") + 1) == 0)
		return (blt_cd(cmd->argc, cmd->args));
	else if (ft_strncmp("pwd", cmd->args[0], ft_strlen("pwd") + 1) == 0)
		return (blt_pwd());
	else if (ft_strncmp("export", cmd->args[0], ft_strlen("export") + 1) == 0)
		return (blt_export(cmd->argc, cmd->args, env));
	else if (ft_strncmp("unset", cmd->args[0], ft_strlen("unset") + 1) == 0)
		printf("unset\n");//blt_unset;
	else if (ft_strncmp("env", cmd->args[0], ft_strlen("env") + 1) == 0)
		printf("env\n");//return (blt_env(cmd->env, NULL, 0));
	else if (ft_strncmp("exit", cmd->args[0], ft_strlen("exit") + 1) == 0)
		exit(blt_exit(cmd->argc, cmd->args));
	return (127);
}

int	is_blt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_tolower(str[i++]);
	if (ft_strncmp("echo", str, ft_strlen("echo") + 1) == 0)
		return (0);
	else if (ft_strncmp("cd", str, ft_strlen("cd") + 1) == 0)
		return (0);
	else if (ft_strncmp("pwd", str, ft_strlen("pwd") + 1) == 0)
		return (0);
	else if (ft_strncmp("export", str, ft_strlen("export") + 1) == 0)
		return (0);
	else if (ft_strncmp("unset", str, ft_strlen("unset") + 1) == 0)
		return (0);
	else if (ft_strncmp("env", str, ft_strlen("env") + 1) == 0)
		return (0);
	else if (ft_strncmp("exit", str, ft_strlen("exit") + 1) == 0)
		return (0);
	return (1);
}
