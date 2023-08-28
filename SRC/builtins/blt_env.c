/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:46:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 19:14:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int print_env(t_env **envp)
{
	t_env	*env;

	// ft_printf(1, "PRINTING ENV\n"); // TODO delete

	env = *envp;
	while (env)
	{
		if (env->val)
			ft_printf(1, "%s=%s\n", env->key, env->val);
		env = env->next;	
	}
	return (0);
}

char **new_env(int argc, char **argv, int *_i)
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

	// ft_printf(1, "CALLING ENV\n"); // TODO delete
	i = 1;
	nw_env = NULL;
	matrix = env_matrix(*envp);
	export_add(matrix, &nw_env);	
	// ft_printf(1, "\nENVS COPIED\n");	//
	vervose_print_envs(nw_env);					//
	// ft_printf(1, "\nfreeing\n");	//
	free_matrix(matrix);
	// ft_printf(1, "\nfreed\n");	//
	
	matrix = NULL;
	matrix = new_env(argc, argv, &i);//size_t
	// ft_printf(1, "\nentering_exportadd\n");	//
	export_add(matrix, &nw_env);	
	// ft_printf(1, "\nNEW ENVS ADDED\n");	//
	print_envs(nw_env);					//
	// ft_printf(1, "\nNEW ENVS PRINTED\n");	//
	free_matrix(matrix);
	// ft_printf(1, "freed\n");	//
	
	matrix = args_envv(argc, argv, &i); //int
// ft_printf(1, "printing args matrix\n");	//
	print_matrix(matrix);
// ft_printf(1, "printed args matrix\n");	//
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
