/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:04:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/04 17:12:30 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	if ((char *)dst > (char *)src)
		while (len-- > 0)
			((char *)dst)[len] = ((char *)src)[len];
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	int b = 50;


	char str[400] = "holaquetalestamos";
	memmove(str+3, str, b);
	printf("%s\n", str);
		
	char str1[400] = "holaquetalestamos";
	ft_memmove(str1+3 , str1, b);
	printf("%s\n", str1);

	char str3[200] = "holaquetalestamos";
	memmove(str3, str3+3, b);
	printf("%s\n", str3);


	char str4[200] = "holaquetalestamos";
	ft_memmove(str4 , str4+3, b);
	printf("%s\n", str4);
	return (0);
}*/
