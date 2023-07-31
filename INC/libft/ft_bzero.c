/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:18:00 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 23:55:58 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "holaque tal roberto";

	printf("%s\n", str);
	
	bzero(str + 2, 3);
	printf("%s", str);
	printf("      %c\n", str[5]);
	
	
	ft_bzero(str + 2, 3);
	printf("%s", str);
	printf("      %c\n", str[5]);
}*/
