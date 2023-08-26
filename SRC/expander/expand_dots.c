/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:18:45 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 20:32:29 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

// static int	dst_doll_brk(char *str, int i);

static char	*getenv_str(char *str)
{
	int		i;
	char	*ret;

	i = dst_doll_brk(str, 1) - 1;
	if (str[i] == '$' || str[i] == ' ')
		i--;
	ret = ft_substr(str, 1, i);
	return (ret);
}

static char	*check_env(char *str)
{
	char	*env;
	char	*aux;

	env = getenv_str(str);
	if (!getenv(env))
		aux = ft_strdup("");
	else
		aux = ft_strdup(getenv(env));
	free(env);
	return (aux);
}

static char	*get_ret(char *ret, char *str, int j)
{
	char	*aux;
	char	*tmp;

	tmp = "\0";
	aux = ft_substr(str, 0, j);
	if (ret[0] != '\0')
		tmp = free_join(ret, tmp);
	ret = ft_strjoin(tmp, aux);
	if (tmp[0] != '\0')
		free(tmp);
	free(aux);
	aux = check_env(str + j);
	tmp = free_join(ret, tmp);
	ret = ft_strjoin(tmp, aux);
	free(tmp);
	free(aux);
	return (ret);
}

static int	get_len(char *str)
{
	char	*env;
	int		i;

	env = getenv_str(str);
	i = ft_strlen(env);
	free(env);
	return (i);
}

char	*expand_dots(t_tokens *tokens, int i, size_t j, char *ret)
{
	char	*str;
	int		len;

	len = tokens->words[i]->len;
	str = tokens->words[i]->word;
	while (str[j])
	{
		if (str[j] == '$')
		{
			if (dst_doll_brk(str, j + 1) > 1)
			{
				ret = get_ret(ret, str, j);
				str = str + j + get_len(str + j) + 1;
				j = 0;
				len--;
			}
		}
		else
			j++;
		if (len-- <= 0)
			break ;
	}
	ret = ft_strjoin(ret, str);
	return (ret);
}
