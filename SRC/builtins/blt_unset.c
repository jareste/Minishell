#include <minishell.h>

static int delete_env(t_env **_env, t_env *prev, t_env *curr)
{
	if (!prev && ! curr->next)
	{
// ft_printf(1, "not prev not next\n");
		*_env = free_env(curr);	
	}
	else if(!prev)
	{
// ft_printf(1, "not prev\n");
		curr = curr->next;
		free_env(curr->prev);
		*_env = curr;
		curr->prev = NULL;
	}
	else if (!curr->next)
	{
// ft_printf(1, "not next\n");
		prev->next = NULL;
		free_env(curr);
	}
	else
	{
// ft_printf(1, "not not any\n");
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
//			len = ft_strlen(curr->key);
//			if (len < ft_strlen(argv[i]))
//				len = ft_strlen(argv[i]);
			len = ft_strlen(curr->key) + 1;
//			ft_printf(1, "Checking: >%s< >%s<\n", curr->key, argv[i]);
			if (ft_strncmp(curr->key, argv[i], len) == 0)
			{
				delete_env(_env, prev, curr);
				break;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}

