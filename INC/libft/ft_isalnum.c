/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:10:04 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 23:48:56 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
	printf("%d", isalnum(c));
	printf("%d\n", ft_isalnum(c));

	c = 'A';
	printf("%d", isalnum(c));
	printf("%d\n", ft_isalnum(c));

	c = 52;
	printf("%d", isalnum(c));
	printf("%d\n", ft_isalnum(c));

	c = '-';
	printf("%d", isalnum(c));
	printf("%d\n", ft_isalnum(c));

	c = 1;
	printf("%d", isalnum(c));
	printf("%d\n", ft_isalnum(c));
	return(0);
}*/
