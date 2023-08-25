#include <minishell.h>

static int delete_env(t_env **_env, t_env *prev, t_env *curr)
{
	if (!prev && ! curr->next)
		*_env = free_env(curr);	
	else if(!prev)
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
	
	i = 0;
	while (*_env && (argv[i]))
	{
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

