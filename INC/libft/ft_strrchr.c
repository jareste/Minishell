/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:29:42 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:13:28 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*memo;

	memo = 0;
	while (*s)
	{
		if (*s == (char)c)
			memo = (char *)s;
		s++;
	}
	if (*s == (char)c)
		memo = (char *)s;
	return (memo);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[50] = "hola que tal estas";
	char *p;
	p = strrchr(str, '\0');
	printf("%s\n", p);

	char str1[50] = "hola que tal estas";
	p = ft_strrchr(str1, '\0');
	printf("%s\n", p);
	return (0);
}
*/
