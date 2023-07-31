/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:39:20 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/06 03:17:19 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[50] = "hola que tal estas";
	char *p;
	p = strchr(str, 'a');
	printf("%s\n", p);

	char str1[50] = "hola que tal estas";
	p = ft_strchr(str1, 'a');
	printf("%s\n", p);
	return (0);
}
*/
