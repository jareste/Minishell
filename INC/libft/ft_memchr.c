/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:48:11 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:07:02 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((((char *)s)[i]) == (char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char c[200] = "holaquetalestas";
	char *p;

	p = memchr(c, 'a', 20);
	printf("%s\n", p);

	char c1[200] = "holaquetalestas";
	p = ft_memchr(c1, 'a', 20);
	printf("%s", p);
	return (0);
}*/
