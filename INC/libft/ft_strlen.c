/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:32:58 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:13:41 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	int a;

	a = strlen("hola que tal");
	printf("%d", a);
	printf("%d\n", ft_strlen("hola que tal"));
	
	a = strlen("hola que tal12345 67 8");
	printf("%d", a);
	printf("%d\n", ft_strlen("hola que tal12345 67 8"));

	a = strlen ("hola que tal   ");	
	printf("%d", a);
	printf("%d\n", ft_strlen("hola que tal   "));
	
	a = strlen("");
	printf("%d", a);
	printf("%d\n", ft_strlen(""));
}*/
