/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:01:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/23 17:14:56 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export_print(t_env *env)
{
	 while (env)
	 {
	 	ft_printf(1, "%s\n", env->key, env->val);
	 	env = env->next;
	 }
	return (0);
}

static int check_bad_char(char * arg)
{
	int c;
	char valid[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

static int	append_env(t_env **_env, char **arg)
{
	t_env		*env;
	size_t		eqi;

	if (!*_env)
	{
		*_env = calloc(sizeof(t_env), 1);
		env = *_env;
	}
	else
	{
		(*_env)->next = calloc(sizeof(t_env), 1);
		env = (*_env)->next;
	}
	if (!env)
		return (1);
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

static int	check_keys(char ***_argv, t_env **_env)
{
	t_env	*env;
	char 	**argv;

	env = *_env;
	argv =*_argv;
	while (env->next)
	{
		if (ft_strncmp(env->key, *argv, ft_strlen(env->key)) == 0) 
		{
			free(env->val);
			env->val = ft_strdup(*argv + ft_ichar(*argv, '=') + 1);
			*_argv = *_argv + 1;
			return (1);
		}
		env = env->next;
	}
	*_env = env;
	return (0);
}

int export_add(char **argv, t_env **_env) 
{
	t_env	*env; // TODO no need to use the second variable can use **_env
	int		ret;

	ret = 0;
	if (!_env)
		append_env(_env, argv++);
	while (*argv)
	{
		ft_printf(1, "Adding: %s\n", *argv);
		env = *_env;
		if (check_bad_char(*argv))
		{
			ret = 1;
			argv++;
			continue ;
		}
		if (check_keys(&argv, &env))
			continue ;
		append_env(&env, argv++);
	}
	return (ret);
}

int blt_export(int argc, char **argv, t_env **env)
{

	if (argc == 1)
		return (export_print(*env));
	else
		return (export_add(argv + 1, env));
}
