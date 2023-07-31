/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:18:37 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 23:50:33 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	char c;

	c = 'a';
	printf("%d", isascii(c));
	printf("%d\n", ft_isascii(c));

	c = 'A';
	printf("%d", isascii(c));
	printf("%d\n", ft_isascii(c));

	c = 'z';
	printf("%d", isascii(c));
	printf("%d\n", ft_isascii(c));

	c = 127;
	printf("%d", isascii(c));
	printf("%d\n", ft_isascii(c));

	c = 1;
	printf("%d", isascii(c));
	printf("%d\n", ft_isascii(c));
	return(0);
}*/
