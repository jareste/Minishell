/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:18:45 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 08:54:33 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

char	*getenv_str(char *str)
{
	int		i;
	char	*ret;

	i = 1;
	while(str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (str[i] == '$' || str[i] == ' ')
		i--;
	ret = ft_substr(str, 1, i);
	return (ret);
}

static char	*free_join(char *ret, char *tmp)
{
	tmp = ft_strdup(ret);
	free(ret);
	return (tmp);
}

char	*expand_dots(t_tokens *tokens, int i)
{
	size_t		j;
	char	*str;
	char	*aux;
	char	*ret;
	char	*env;
	char	*tmp;
	int		len;

	len = tokens->words[i]->len;
	str = tokens->words[i]->word;
	j = 0;
	ret = "\0";
	tmp = "\0";
	while (str[j])
	{
		if (str[j] == '$')
		{
			aux = ft_substr(str, 0, j);
			if (ret[0] != '\0')
				tmp = free_join(ret, tmp);
			ret = ft_strjoin(tmp, aux);
			if (tmp[0] != '\0')
				free(tmp);
			free(aux);
			env = getenv_str(str + j);
			if (!getenv(env))
				aux = ft_strdup("");
			else
				aux = ft_strdup(getenv(env));
			tmp = free_join(ret, tmp);
			ret = ft_strjoin(tmp, aux);
			free(tmp);
			str = str + j + ft_strlen(env) + 1;
			free(aux);
			free(env);
			j = 0;
			len--;
		}
		else
			j++;
		if (len-- <= 0)
			break ;
	}
	if (ret[0] != '\0')
		tmp = free_join(ret, tmp);
	
	// {
	// 	tmp = ft_strdup(ret);
	// 	free(ret);
	// }
	ret = ft_strjoin(tmp, str);
	free(tmp);
	return (ret);
}
