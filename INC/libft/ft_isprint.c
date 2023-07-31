/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:26:26 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 23:53:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
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
	printf("%d", isprint(c));
	printf("%d\n", ft_isprint(c));

	c = 'A';
	printf("%d", isprint(c));
	printf("%d\n", ft_isprint(c));

	c = 'z';
	printf("%d", isprint(c));
	printf("%d\n", ft_isprint(c));

	c = 126;
	printf("%d", isprint(c));
	printf("%d\n", ft_isprint(c));

	c = 1;
	printf("%d", isprint(c));
	printf("%d\n", ft_isprint(c));
	return(0);
}*/
