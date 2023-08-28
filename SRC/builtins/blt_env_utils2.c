/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:26:44 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/28 21:28:36 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

char	**tokens_to_matrix(t_tokens *tokens)
{
	char	**nw_mtrx;
	size_t	len;

	len = tokens->size;
	nw_mtrx = (char **) malloc(sizeof(char *) * (len + 1));
	if (!nw_mtrx)
		return (NULL);
	nw_mtrx[len] = NULL;
	while (1)
	{
		len--;
		nw_mtrx[len] = ft_strdup(tokens->words[len]->word); 
		if (len == 0)
			break ;
	}
	return (nw_mtrx);
}

void	vervose_print_envs(t_env *env)
{
	while (env)
	{
		ft_printf(1, "%p: %p,%p \n\t >%s<=>%s<\n", env, env->prev, \
		env->next, env->key, env->val);
		env = env->next;
	}
}

void	print_envs(t_env *env)
{
	while (env)
	{
		ft_printf(1, "%s=%s\n", env->key, env->val);
		env = env->next;
	}
}

char	*ft_strndup(char *str, size_t i)
{
	char	*str_res;

	if (!str)
		return (NULL);
	str_res = malloc(sizeof(char) * (i + 1));
	str_res[i] = '\0';
	while (i--)
		str_res[i] = str[i];
	return (str_res);
}

int	ft_ichar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}
