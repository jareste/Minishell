/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:38 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/04 17:17:41 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int c;

	c = '8';
	printf("%d", isdigit(c));
	printf("%d\n", ft_isdigit(c));

	c = 'A';
	printf("%d", isdigit(c));
	printf("%d\n", ft_isdigit(c));

	c = 52;
	printf("%d", isdigit(c));
	printf("%d\n", ft_isdigit(c));

	c = '-';
	printf("%d", isdigit(c));
	printf("%d\n", ft_isdigit(c));

	c = 1;
	printf("%d", isdigit(c));
	printf("%d\n", ft_isdigit(c));
	return(0);
}*/
