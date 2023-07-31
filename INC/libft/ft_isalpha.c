/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:45:38 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 23:50:06 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
int main(void)
{
	char c;

	c = 'a';
	printf("%d", isalpha(c));
	printf("%d\n", ft_isalpha(c));
	
	c = 'A';
	printf("%d", isalpha(c));
	printf("%d\n", ft_isalpha(c));
	
	c = 'z';
	printf("%d", isalpha(c));
	printf("%d\n", ft_isalpha(c));
	
	c = '-';
	printf("%d", isalpha(c));
	printf("%d\n", ft_isalpha(c));
	
	c = '1';
	printf("%d", isalpha(c));
	printf("%d\n", ft_isalpha(c));
	return(0);
}*/
