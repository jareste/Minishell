/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:11:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/20 21:44:45 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

char	*free_join(char *ret, char *tmp)
{
	tmp = ft_strdup(ret);
	free(ret);
	return (tmp);
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
		printf("entro\n");
		i++;
		j++;
	}
	return (j + 1);
}

char	*expand_dollar(t_tokens *tokens, int i)
{
	char	*str;
	int		type;
	char	*tmp;
	char	*tmp2;

	if ((int)tokens->size <= i + 1)
		return (ft_strdup("$"));
	type = tokens->words[i + 1]->type;
	// if (type == 4)
	// {
		// str = "$";
		// return (str);
	// }
	str = tokens->words[i + 1]->word;
	// printf("dst:::::%i,len::::%i,\n", dst_doll_brk(str, 0), (int)ft_strlen(str));
	if (dst_doll_brk(str, 0) == (int)ft_strlen(str))
	{
		if (!getenv(str))
			return (ft_strdup(""));
		tmp = ft_strdup(getenv(str));
		return (tmp);
	}
	else
	{
		tmp = ft_substr(str, 0, dst_doll_brk(str, 0) - 1);
		tmp2 = ft_substr(str, dst_doll_brk(str, 0) - 1, 1 + (int)ft_strlen(str) - dst_doll_brk(str, 0));
		str = getenv(tmp);
		free(tmp);
		tmp = ft_strjoin(str, tmp2);
		// printf("tmp::::::%s,tmp2:::::%s,\n::str:%s\n", str, tmp2, tmp);
		free(tmp2);
		return (tmp);
	}
	return (NULL);

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
