/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:46:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/22 16:02:59 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int print_env(t_env **envp)
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

int	blt_envv(int argc, char **argv, t_env **envp)
{
	if (argc == 1)
		return (print_env(envp));
	if (!argc)
		ft_printf(1, "env:%p", argv);
	return (0);
	
}


/*
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
	return (i);
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
}*/
