/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:46:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 20:29:47 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	print_env(t_env **envp)
{
	t_env	*env;

	env = *envp;
	while (env)
	{
		if (env->val)
			ft_printf(1, "%s=%s\n", env->key, env->val);
		env = env->next;
	}
	return (0);
}

char	**new_env(int argc, char **argv, int *_i)
{
	int			i;
	t_tokens	*tk_envs;
	char		**char_envs;

	tk_envs = msh_start_words(NULL);
	i = 1;
	while (i < argc && ft_strchr(argv[i], '='))
	{
		if (!msh_add_word(tk_envs, argv[i], ft_strlen(argv[i]), 0))
		{
			msh_free_tokens(tk_envs);
			return (NULL);
		}
		i++;
	}
	msh_mount_matrix(tk_envs);
	char_envs = tokens_to_matrix(tk_envs);
	msh_free_tokens(tk_envs);
	*_i = i;
	return (char_envs);
}

char	**args_envv(int argc, char **argv, int *_i)
{
	int			i;
	char		**nw_args;
	t_tokens	*aux_args;

	aux_args = msh_start_words(NULL);
	i = *_i;
	while (i < argc)
	{
		if (!msh_add_word(aux_args, argv[i], ft_strlen(argv[i]), 0))
		{
			msh_free_tokens(aux_args);
			return (NULL);
		}
		i++;
	}
	msh_mount_matrix(aux_args);
	nw_args = tokens_to_matrix(aux_args);
	msh_free_tokens(aux_args);
	*_i = i;
	return (nw_args);
}

int	call_envv(int argc, char **argv, t_env **envp)
{
	int		i;
	t_env	*nw_env;
	char	**matrix;

	i = 1;
	nw_env = NULL;
	matrix = env_matrix(*envp);
	export_add(matrix, &nw_env);
	vervose_print_envs(nw_env);
	free_matrix(matrix);
	matrix = NULL;
	matrix = new_env(argc, argv, &i);
	export_add(matrix, &nw_env);
	print_envs(nw_env);
	free_matrix(matrix);
	matrix = args_envv(argc, argv, &i);
	print_matrix(matrix);
	exit(0);
	return (0);
}

int	blt_envv(int argc, char **argv, t_env **envp)
{
	if (argc == 1)
		return (print_env(envp));
	if (!argc)
		ft_printf(1, "env:%p", argv);
	else
		call_envv(argc, argv, envp);
	return (0);
}
