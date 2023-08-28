/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:02:22 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 21:31:20 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*catenv(char *key, char *val)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, val);
	free(temp);
	return (result);
}

char	**free_matrix(char **matrix)
{
	size_t	s;

	s = 0;
	while (matrix[s])
		free(matrix[s++]);
	free(matrix);
	return (NULL);
}

void	print_matrix(char **matrix)
{
	while (*matrix)
	{
		ft_printf(1, ">%s<\n", *matrix);
		matrix++;
	}
}

char	**env_matrix(t_env *_envs)
{
	t_env	*envs;
	size_t	size;
	char	**matrix;

	size = 0;
	envs = _envs;
	while (envs)
	{
		if (envs->val)
			size++;
		envs = envs->next;
	}
	matrix = calloc(sizeof(char *), size + 1);
	envs = _envs;
	size = 0;
	while (envs)
	{
		if (envs->val)
			matrix[size] = catenv(envs->key, envs->val);
		if (envs->val)
			size++;
		envs = envs->next;
	}
	return (matrix);
}

t_env	*env_list(char **envs)
{
	t_env	*first;
	t_env	*curr;

	first = (t_env *) calloc(sizeof(t_env), 1);
	if (!first)
		return (free_envs(&first));
	curr = first;
	curr->key = ft_strndup(*envs, ft_ichar(*envs, '='));
	curr->val = ft_strdup(*envs + ft_ichar(*envs, '=') + 1);
	envs++;
	while (envs && *envs)
	{
		curr->next = (t_env *) calloc(sizeof(t_env), 1);
		if (!curr->next)
			return (free_envs(&first));
		curr->next->prev = curr;
		curr = curr->next;
		curr->key = ft_strndup(*envs, ft_ichar(*envs, '='));
		curr->val = ft_strdup(*envs + ft_ichar(*envs, '=') + 1);
		if (!curr->key || !curr->val)
			return (free_envs(&first));
		envs++;
	}
	return (first);
}
