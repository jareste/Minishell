# include <minishell.h>

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

	str_res = malloc(sizeof(char) * (i + 1));
	str_res[i] = '\0';
	while(i--)
		str_res[i] =  str[i];
	return (str_res);

}

int ft_ichar(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

t_env *free_envs(t_env *env_nodes)
{
	t_env *aux;

	while (env_nodes)
	{
		aux = env_nodes;
		free(env_nodes->key);
		free(env_nodes->val);
		env_nodes = env_nodes->next;
		free(aux);
	}
	return (NULL);
}

t_env *env_get_last(t_env *env)
{
	while (env->next)
		env = env->next;
	return (env);
}


t_env	*env_list(char **envs)
{
	t_env	*first;
	t_env	*curr;

	first = (t_env *) calloc(sizeof(t_env), 1);
	if(!first)
		return (free_envs(first));
	curr = first;
	curr->key = ft_strndup(*envs, ft_ichar(*envs, '='));
	curr->val = ft_strdup(*envs + ft_ichar(*envs, '=') + 1);
	envs++;
	while(envs &&*envs)
	{
		curr->next = (t_env *) calloc(sizeof(t_env), 1);
		if(!curr->next)
			return (free_envs(first));
		curr->next->prev = curr;
		curr = curr->next;

		curr->key = ft_strndup(*envs, ft_ichar(*envs, '='));
		curr->val = ft_strdup(*envs + ft_ichar(*envs, '=') + 1);
		if (!curr->key || !curr->val)
			return (free_envs(first));
		envs++;
	}
	return (first);
}
