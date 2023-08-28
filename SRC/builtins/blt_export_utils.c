/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:34:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 20:51:46 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

t_env	*last_env(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

char	*ft_getenv(t_env *env, char *target)
{
	while (env)
	{
		if (ft_strncmp(env->key, target, ft_strlen(env->key) + 1) == 0)
		{
			return (ft_strdup(env->val));
		}
		env = env->next;
	}
	return (NULL);
}

int	export_add(char **argv, t_env **_env)
{
	int		ret;

	ret = 0;
	if (!*_env && append_env(_env, argv++))
		return (1);
	while (*argv)
	{
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

int	check_keys(char ***_argv, t_env **_env)
{
	t_env	*env;
	char	**argv;
	int		len;

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
