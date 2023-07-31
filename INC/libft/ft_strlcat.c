/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:42:38 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:19:20 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;
	char	*s;
	size_t	retvalue;

	s = (char *)src;
	i = 0;
	len_d = ft_strlen(dst);
	len_s = ft_strlen(s);
	if (dstsize > len_d)
		retvalue = len_s + len_d;
	else
		retvalue = len_s + dstsize;
	while (*dst)
		dst++;
	while (s[i] && i + len_d + 1 < dstsize)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (retvalue);
}
