/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:11:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 20:46:12 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

char	*free_join(char *ret, char *tmp)
{
	tmp = ft_strdup(ret);
	free(ret);
	return (tmp);
}

int	dst_doll_brk(char *str, int i)
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

static char	*aux_expand_dollar(char *str, char *tmp)
{
	char	*tmp2;

	tmp = ft_substr(str, 0, dst_doll_brk(str, 0) - 1);
	tmp2 = ft_substr(str, dst_doll_brk(str, 0) \
	- 1, 1 + (int)ft_strlen(str) - dst_doll_brk(str, 0));
	str = getenv(tmp);
	free(tmp);
	if (str)
		tmp = ft_strjoin(str, tmp2);
	else
		return (tmp2);
	free(tmp2);
	return (tmp);
}

char	*expand_dollar(t_tokens *tokens, int i, int err[2])
{
	int		type;
	char	*tmp;

	tmp = NULL;
	if ((int)tokens->size <= i + 1)
		return (ft_strdup("$"));
	type = tokens->words[i + 1]->type;
	if (tokens->words[i + 1]->word[0] == '?')
	{
		if (sig_rec != 0)
			return (ft_itoa(sig_rec));
		else
			return (ft_itoa(err[1]));
	}
	if (dst_doll_brk(tokens->words[i + 1]->word, 0) \
	== (int)ft_strlen(tokens->words[i + 1]->word))
	{
		if (!getenv(tokens->words[i + 1]->word))
			return (ft_strdup(""));
		tmp = ft_strdup(getenv(tokens->words[i + 1]->word));
	}
	else
		tmp = aux_expand_dollar(tokens->words[i + 1]->word, tmp);
	return (tmp);
}

char	*merge_matrix(char **matrix, int len)
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
		if (i > len)
			break ;
	}
	return (ret);
}
