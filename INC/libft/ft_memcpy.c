/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:37:05 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:02:57 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src && !dst)
		return (0);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
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
	memcpy(str+3, str, b);
	printf("%s\n", str);

	char str1[400] = "holaquetalestamos";
	ft_memcpy(str1+3 , str1, b);
	printf("%s\n", str1);

	char str3[200] = "holaquetalestamos";
	memcpy(str3, str3+3, b);
	printf("%s\n", str3);


	char str4[200] = "holaquetalestamos";
	ft_memcpy(str4 , str4+3, b);
	printf("%s\n", str4);
	return (0);

}*/
