/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:01:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/22 18:58:18 by jrenau-v         ###   ########.fr       */
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

int export_add(int argc, char ** argv, t_env **_env) 
{
	size_t	eqi;
	t_env	*env;

	//TODO gestionar el NULL
	if (argc < 1)  // Optatiu :?
		return (1);
	while (*argv)
	{
		env = *_env;
		while (env->next)
		{
			if (ft_strncmp(env->key, *argv, ft_strlen(env->key)) == 0) 
			{
				env->val = *argv;
				return (0);
			}
			env = env->next;
		}
		env->next = calloc(sizeof(t_env), 1);
		eqi = ft_ichar(*argv, '=');
		ft_printf(1, "argv: %s\n", *argv);
		env->next->key = ft_strndup(*argv, eqi);
		env->next->val = ft_strdup(*argv + eqi + 1);
		argv++;
		return (0);
	}
	return (0);
}

int blt_export(int argc, char **argv, t_env **env)
{
	if (argc == 1)
		return (export_print(*env));
	else
		return (export_add(argc, argv + 1, env));
}
