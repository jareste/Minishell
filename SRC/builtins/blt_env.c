/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:46:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/20 09:46:48 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static char	**create_env(char **env, int env_size)
{
	int		i;
	char	**envtmp;
	char	**envc;

	i = 0;
	envtmp = env;
	while (*envtmp)
	{
		env_size++;
		envtmp++;
	}
	envc = ft_calloc(sizeof(char *), env_size);
	if (!envc)
		return (NULL); //failed to create envc
	envtmp = env;
	i = 0;
	while (*envtmp)
	{
		envc[i] = ft_strdup(*envtmp);
		i++;
		envtmp++;
	}
	return (envc);
}

int	ft_envlen(char **env)
{
	int	i;

	i = 0;
	while (*env)
	{
		i++;
		env++;
	}
	return (i + 20);
}

void	print_env(char **envc)
{
	int	i;

	i = 0;
    while (envc[i]) 
    {
        printf("%s\n", envc[i]);
        i++;
	}
}



int	blt_env(char **env, char *str, int to_do)
{
	// static char	**envc = NULL;
	static int	env_size = 0;

	if (env_size == 0)
		env_size = ft_envlen(env);
	
	if (!envc)
		envc = create_env(env, env_size);
	if (to_do == 1)
		add_env(str, envc);
	(void)str;
	(void)to_do;
	print_env(envc);
	return (0);
}
