/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:29:53 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 21:31:09 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

t_env	*free_env(t_env *env)
{
	free(env->key);
	free(env->val);
	free(env);
	return (NULL);
}

t_env	*free_envs(t_env **_env_nodes)
{
	t_env	*aux;
	t_env	*env_nodes;

	if (!*_env_nodes)
		return (NULL);
	env_nodes = *_env_nodes;
	while (env_nodes)
	{
		aux = env_nodes;
		env_nodes = env_nodes->next;
		free_env(aux);
	}
	*_env_nodes = NULL;
	return (NULL);
}

t_env	*env_get_last(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

char	**dup_matrix(char **matrix, size_t len)
{
	char	**nw_mtrx;

	nw_mtrx = (char **) malloc(sizeof(char *) * (len + 1));
	if (!nw_mtrx)
		return (NULL);
	nw_mtrx[len] = NULL;
	while (1)
	{
		len--;
		nw_mtrx[len] = ft_strdup(matrix[len]); 
		if (len == 0)
			break ;
	}
	return (nw_mtrx);
}
