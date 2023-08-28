/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:36:44 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 19:38:44 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	delete_env(t_env **_env, t_env *prev, t_env *curr)
{
	if (!prev && ! curr->next)
		*_env = free_env(curr);
	else if (!prev)
	{
		curr = curr->next;
		free_env(curr->prev);
		*_env = curr;
		curr->prev = NULL;
	}
	else if (!curr->next)
	{
		prev->next = NULL;
		free_env(curr);
	}
	else
	{
		curr = curr->next;
		free_env(curr->prev);
		curr->prev = prev;
		prev->next = curr;
	}
	return (0);
}

int	blt_unset(char **argv, t_env **_env)
{
	t_env	*prev;
	t_env	*curr;
	int		i;
	size_t	len;

	i = 0;
	while (*_env && (argv[i]))
	{
		prev = NULL;
		curr = *_env;
		while (curr)
		{
			len = ft_strlen(curr->key) + 1;
			if (ft_strncmp(curr->key, argv[i], len) == 0)
			{
				delete_env(_env, prev, curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}
