/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:55:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:15:59 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;

	newstr = (char *)malloc(ft_strlen(s1) + 1);
	if (newstr == NULL)
		return (0);
	ft_memcpy(newstr, s1, ft_strlen(s1) + 1);
	return (newstr);
}
/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char c[20] = "lentibobo";
	char *ptr;

	ptr = strdup(c);
	printf("%s\n", ptr);

	char c1[20] = "lentibobo";
	char *ptr1;

	ptr1 = ft_strdup(c1);
	printf("%s\n", ptr1);
	return (0);
}*/
