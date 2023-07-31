/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:01:03 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/03 03:49:10 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_free_split(char **split, size_t i)
{
	while (i-- > 0)
		free(split[i]);
	free(split);
	return (NULL);
}

static int	ft_countc(char const *s, char c)
{
	size_t	i;
	int		cnt;

	i = 1;
	cnt = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c)
		cnt++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			cnt++;
		if (s[i] != c && s[i - 1] == c)
			cnt++;
		i++;
	}
	if (s[i] == c && cnt != 1)
		return (cnt / 2);
	else
		cnt++;
	return (cnt / 2);
}

static size_t	ft_nextcin(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**split;
	size_t	len;
	size_t	len_sub;

	len = ft_countc(s, c);
	split = (char **)malloc(sizeof(char *) * (len + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < len && *s)
	{
		while (*s == c)
			s++;
		len_sub = ft_nextcin(s, c);
		split[i] = ft_substr(s, 0, len_sub);
		if (split[i] == NULL)
			return (ft_free_split(split, i));
		s += len_sub;
		i++;
	}
	split[i] = NULL;
	return (split);
}
