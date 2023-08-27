/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 04:02:22 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/25 14:43:25 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

char **dup_matrix(char **matrix, size_t len)
{
	char	**nw_mtrx;
	
	nw_mtrx = (char **) malloc(sizeof(char *) * (len + 1));
	if (!nw_mtrx)
		return (NULL);
	nw_mtrx[len] = '\0';
	while (1)
	{
		len--;
		nw_mtrx[len] = ft_strdup(matrix[len]); 
		if (len == 0)
			break;
	}
	return (nw_mtrx);
}

char **tokens_to_matrix(t_tokens *tokens)
{
	char	**nw_mtrx;
	size_t	len;
	
	
	len = tokens->size;
	nw_mtrx = (char **) malloc(sizeof(char *) * (len + 1));
	if (!nw_mtrx)
		return (NULL);
	nw_mtrx[len] = '\0';
	while (1)
	{
		len--;
		nw_mtrx[len] = ft_strdup(tokens->words[len]->word); 
		if (len == 0)
			break;
	}
	return (nw_mtrx);
}

void vervose_print_envs(t_env *env) // TODO es pot borrar per passar norminette
{
	while (env)
	{
		ft_printf(1, "%p: %p,%p \n\t >%s<=>%s<\n", env, env->prev, env->next, env->key, env->val);
		env = env->next;
	}
}

void print_envs(t_env *env)
{
	while (env)
	{
		ft_printf(1, "%s=%s\n",env->key, env->val);
		env = env->next;
	}
}

char *ft_strndup(char *str, size_t i)
{
	char *str_res;

	if (!str)
		return (NULL);
	str_res = malloc(sizeof(char) * (i + 1));
	str_res[i] = '\0';
	while(i--)
	{
		str_res[i] =  str[i];
	}
	return (str_res);
}

int ft_ichar(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

t_env	*free_env(t_env *env)
{
	free(env->key);
	free(env->val);
	free(env);
	return (NULL);
}
t_env *free_envs(t_env **_env_nodes)
{
	t_env *aux;
	t_env *env_nodes;

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

t_env *env_get_last(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

static char *catenv(char *key, char *val)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result  = ft_strjoin(temp, val);
	free(temp);
	return (result);
}

char **free_matrix(char **matrix)
{
	size_t s;

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
	
char **env_matrix(t_env *_envs)
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
	matrix = calloc(sizeof(char *), size + 1); //TODO not protected 
	envs = _envs;
	size = 0;
	while (envs)
	{
		if (envs->val)
			matrix[size] = catenv(envs->key, envs->val); //TODO not protected
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
	if(!first)
		return (free_envs(&first));
	curr = first;
	curr->key = ft_strndup(*envs, ft_ichar(*envs, '='));
	curr->val = ft_strdup(*envs + ft_ichar(*envs, '=') + 1);
	envs++;
	while(envs &&*envs)
	{
		curr->next = (t_env *) calloc(sizeof(t_env), 1);
		if(!curr->next)
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
