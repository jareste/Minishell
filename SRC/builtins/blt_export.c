/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:01:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 20:51:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_bad_char(char *arg)
{
	int		c;
	char	*valid;

	valid = "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (!ft_strchr(valid + 10, arg[0])) 
	{
		ft_printf(2, "export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	c = 1;
	while (arg[c] && arg[c] != '=')
	{
		if (!ft_strchr(valid, arg[c]))
		{
			ft_printf(2, "export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		c++;
	}
	return (0);
}

static int	aux_append_env(t_env *env, char **arg, size_t eqi)
{
	eqi = ft_ichar(*arg, '=');
	if (eqi == (size_t) -1)
	{
		env->key = ft_strdup(*arg);
		env->val = NULL;
	}
	else if (eqi == ft_strlen(*arg) + 1)
	{
		env->key = ft_strdup(*arg);
		env->val = "";
	}
	else
	{
		env->key = ft_strndup(*arg, eqi);
		env->val = ft_strdup(*arg + eqi + 1);
	}
	return (0);
}

int	append_env(t_env **_env, char **arg)
{
	t_env		*env;

	if (!*_env)
	{
		*_env = ft_calloc(sizeof(t_env), 1);
		env = *_env;
	}
	else
	{
		env = last_env(*_env);
		(env)->next = ft_calloc(sizeof(t_env), 1);
		env->next->prev = env; 
		env = env->next;
	}
	if (!env)
		return (1);
	return (aux_append_env(env, arg, 0));
}

static int	print_export(t_env **envp)
{
	t_env	*env;

	env = *envp;
	while (env)
	{
		if (!env->val)
			ft_printf(1, "declare -x %s\n", env->key);
		else if (env->val[0] == '\0')
			ft_printf(1, "declare -x %s=\"\"\n", env->key);
		else
			ft_printf(1, "declare -x %s=\"%s\"\n", env->key, env->val);
		env = env->next;
	}
	return (0);
}

int	blt_export(int argc, char **argv, t_env **env)
{
	if (argc == 1)
		return (print_export(env));
	else
		return (export_add(argv + 1, env));
}
