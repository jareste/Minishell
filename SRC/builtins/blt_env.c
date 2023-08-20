/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:46:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/20 05:02:23 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static void	create_env(t_env *s_env, char **env)
{
	int		i;
	char	**envtmp;

	// envtmp = env;
	i = 0;
	envtmp = env;
	while (*envtmp)
	{
		i++;
		envtmp++;
	}
	s_env->envc = ft_calloc(sizeof(char *), i + 1);
	if (!s_env->envc)
		return ; //failed to allocate envc;
	envtmp = env;
	i = 0;
	while (*envtmp)
	{
		s_env->envc[i] = ft_strdup(*envtmp);
		i++;
		envtmp++;
	}
	envtmp = s_env->envc;
    while (*envtmp != NULL) 
    {
        printf("%s\n", *envtmp);
        envtmp++;
	}
}

int	blt_env(char **env)
{
	t_env	*s_env;

	// if (!s_env)
	// {
		s_env = malloc(sizeof(t_env));
		if (!s_env)
			return (1); //failed to create env;
		create_env(s_env, env);
	// }
	return (0);
}
