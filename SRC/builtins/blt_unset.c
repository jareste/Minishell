#include <minishell.h>

static int delete_env(t_env **_env, t_env *prev, *curr)
{
		if (!prev && ! curr->next)
			*_env = free_env(curr);	
		else if(!prev)
		{
			curr = curr->next;
			free_env(curr);
			*_env = curr;
			curr->prev = NULL;
		}
		else
		{
			curr = curr->next;
			free_env(curr);
			curr->prev = prev;
			prev->next = next;
		}
}
int	blt_unset(char **argv, t_env **_env)
{
	t_env	*prev;
	t_env	*curr;
	int		i;
	
	i = 0;
	while (argv[i])
	{
		if (!*_env)
			return (0);	
		prev = NULL;
		curr = *_env;
		while (curr)
		{
			if (ft_strncmp(curr->key, argv[i], ft_strlen(argv[i])))
			{
				delete_env(_env, prev, curr);
				break;
			}
			curr = curr->next;
		}
	}
	return (0);
}

