/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:01:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/25 11:14:38 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//int	export_print(t_env *env)
//{
//	 while (env)
//	 {
//	 	ft_printf(1, "%s\n", env->key, env->val);
//	 	env = env->next;
//	 }
//	return (0);
//}

static int check_bad_char(char * arg)
{
	int c;
	char valid[] = "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

t_env	*last_env(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

static int	append_env(t_env **_env, char **arg)
{
	t_env		*env;
	size_t		eqi;

	if (!*_env)
	{
		ft_printf(1, "adding to NULL env %p\n", _env);
		*_env = ft_calloc(sizeof(t_env), 1);// TODO not protected
		env = *_env;
	}
	else
	{
		ft_printf(1, "adding to not NULL env %p\n", *_env);
		env = last_env(*_env);
		(env)->next = ft_calloc(sizeof(t_env), 1); //TODO not protected
		env->next->prev = env; 
		env = env->next;
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

static int	check_keys(char ***_argv, t_env **_env) //TODO reduce one pointer to **env
{
	t_env	*env;
	//t_env	*aux;
	char 	**argv;
	int 	len;

	ft_printf(1, "Checkinggg\n");
	env = *_env;
	argv = *_argv;
	while (env)
	{
		len = ft_ichar(*argv, '=');
		if (len < 0)
			len = ft_strlen(*argv);
		if (len < (int) ft_strlen(env->key))
			len = ft_strlen(env->key);
		if (ft_strncmp(env->key, *argv, len) == 0) 
		{
			free(env->val);
			env->val = ft_strdup(*argv + ft_ichar(*argv, '=') + 1);
			*_argv = *_argv + 1;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int export_add(char **argv, t_env **_env) 
{
//	t_env	*env; // TODO no need to use the second variable can use **_env
	int		ret;

	ret = 0;
	if (!*_env && append_env(_env, argv++))
		return (1);
	while (*argv)
	{
//	env = *_env;
		if (check_bad_char(*argv))
		{
			ret = 1;
			argv++;
			continue ;
		}
		if (check_keys(&argv, _env))
			continue ;
		append_env(_env, argv++);

	}
	return (ret);
}

static int print_export(t_env **envp)
{
	t_env	*env;

	env = *envp;
	while (env)
	{
		if (!env->val)
			ft_printf(1, "declare -x %s\n", env->key);
		else if (env->val[0] == '\0')
			ft_printf(1, "declare -x %s=""\n", env->key);
		else
			ft_printf(1, "declare -x %s=%s\n", env->key, env->val);
		env = env->next;	
	}
	return (0);
}


int blt_export(int argc, char **argv, t_env **env)
{
	if (argc == 1)
		return (print_export(env));
	else
		return (export_add(argv + 1, env));
}
