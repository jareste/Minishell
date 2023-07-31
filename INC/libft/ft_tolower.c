/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:34:14 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:13:56 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + ' ';
	return (c);
}
/*

#include <ctype.h>
#include <stdio.h>
int main(void)
{
	printf("%c", tolower('a'));
	printf("%c\n", ft_tolower('a'));

	printf("%c", tolower('A'));
	printf("%c\n", ft_tolower('A'));

	printf("%c", tolower('-'));
	printf("%c\n", ft_tolower('-'));

	printf("%c", tolower('/'));
	printf("%c\n", ft_tolower('/'));

	printf("%c", tolower('2'));
	printf("%c\n", ft_tolower('2'));

	printf("%c", tolower(102));
	printf("%c\n", ft_tolower(102));
	return (0);
}*/
