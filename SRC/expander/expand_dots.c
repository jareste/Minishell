/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:18:45 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 08:08:19 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

char	*getenv_str(char *str)
{
	int	i;

	i = 1;
	while(str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (str[i] == '$' || str[i] == ' ')
		i--;
	return (ft_substr(str, 1, i));
}



char	*expand_dots(t_tokens *tokens, int i)
{
	size_t		j;
	char	*str;
	char	*aux;
	char	*ret;
	char	*env;
	int		len;

	len = tokens->words[i]->len;
	str = tokens->words[i]->word;
	j = 0;
	ret = "\0";
	while (str[j])
	{
		if (str[j] == '$')
		{
			aux = ft_substr(str, 0, j);
			ret = ft_strjoin(ret, aux);
			free(aux);
			env = getenv_str(str + j);
			printf("env:::::::%s\n", env);
			if (!getenv(env))
				aux = ft_strdup("");
			else
			{
				aux = getenv(env);
				aux = ft_strdup(aux);
			printf("aux:::::::%s\n", aux);
			}
			ret = ft_strjoin(ret, aux);
			printf("len:::::%zu\n", ft_strlen(env));
			str = str + j + ft_strlen(env) + 1;
			free(aux);
			j = 0;
			printf("ret:::::::%s\n", ret);
			len--;
		}
		else
			j++;
		if (len-- <= 0)
			break ;
		// printf("len:::%i\n", len);
	}
	ret = ft_strjoin(ret, str);
	printf("ret:::::::%s\n", ret);
	return (ret);
}
