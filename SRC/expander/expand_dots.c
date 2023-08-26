/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:18:45 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 10:55:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static char	*getenv_str(char *str)
{
	int		i;
	char	*ret;

	i = 1;
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
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

static int	dst_doll_brk(char *str, int i)
{
	char	*ok_char;
	int		j;

	ok_char = "_0123456789abcdefghijklmnopqrstuvwxyz\
				ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	j = 0;
	while (str[i] && ft_strrchr(ok_char, str[i]))
	{
		i++;
		j++;
	}
	return (j + 1);
}

char	*expand_dots(t_tokens *tokens, int i, size_t j)
{
	char	*str;
	char	*ret;
	char	*tmp;
	int		len;

	len = tokens->words[i]->len;
	str = tokens->words[i]->word;
	ret = "\0";
	tmp = "\0";
	while (str[j])
	{
		if (str[j] == '$')
		{
			if (dst_doll_brk(str, j) > 1)
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
	if (ret[0])
	{
		tmp = ft_strdup(ret);
		free(ret);
	}
	ret = ft_strjoin(tmp, str);
	if (tmp[0])
		free(tmp);
	return (ret);
}
