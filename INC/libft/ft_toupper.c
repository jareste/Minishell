/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:17:21 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:14:11 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - ' ';
	return (c);
}
/*

#include <ctype.h>
#include <stdio.h>
int main(void)
{
	printf("%c", toupper('a'));
	printf("%c\n", ft_toupper('a'));
	
	printf("%c", toupper('A'));
	printf("%c\n", ft_toupper('A'));
	
	printf("%c", toupper('-'));
	printf("%c\n", ft_toupper('-'));
	
	printf("%c", toupper('/'));
	printf("%c\n", ft_toupper('/'));
	
	printf("%c", toupper('2'));
	printf("%c\n", ft_toupper('2'));
	
	printf("%c", toupper(102));
	printf("%c\n", ft_toupper(102));
	return (0);
}*/
