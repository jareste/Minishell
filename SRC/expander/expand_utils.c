/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:11:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 09:18:36 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

char	*free_join(char *ret, char *tmp)
{
	tmp = ft_strdup(ret);
	free(ret);
	return (tmp);
}

char	*expand_dollar(t_tokens *tokens, int i)
{
	char	*str;
	int		type;

	type = tokens->words[i + 1]->type;
	if (type == 4)
	{
		str = "$";
		return (str);
	}
	str = tokens->words[i + 1]->word;
	if (!getenv(str))
		return (ft_strdup(""));
	return (getenv(str));
}

char	*merge_matrix(char **matrix)
{
	char	*str;
	int		i;
	char	*ret;

	i = 0;
	str = "\0";
	ret = "\0";
	while (matrix[i])
	{
		printf("hola\n");
		if (i > 0)
		{
			str = ft_strdup(ret);
			free(ret);
		}
		ret = ft_strjoin(str, matrix[i]);
		if (i > 0)
			free(str);
		i++;
	}
	return (ret);
}
