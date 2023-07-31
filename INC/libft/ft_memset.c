/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:55:53 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:00:30 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *b, int c, unsigned long long len)
{
	unsigned char	*uc;
	int				i;

	i = 0;
	uc = (unsigned char *)b;
	while (i < (int)len)
	{
		uc[i] = c;
		i++;
	}
	return ((void *)uc);
}
/*

#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "hola que tal";
	printf("%s\n", str);

	memset(str + 2, 'n', 8);
	printf("%s\n", str);
	
	ft_memset(str + 2, 'n', 8);
	printf("%s\n", str);

	char str2[] = " me caes bastante mal la verdad";
	printf("%s\n", str2);

	memset(str2 + 2, 'n', 29);
	printf("%s\n", str2);

	ft_memset(str2 + 2, 'n', 29);
	printf("%s", str2);

	return (0);
}*/
