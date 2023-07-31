/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:15:19 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:12:20 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	temp;

	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < n)
	{
		temp = 0;
		while (needle[temp] != '\0' && haystack[i + temp] != '\0'
			&& haystack[i + temp] == needle[temp] && temp + i < n)
			temp++;
		if (needle[temp] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}
/*

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *searchingFor = "aaabcabcd";
	char *in = "aabc";
//	printf("%s\n", ft_strnstr(in, searchingFor, 5));
//	printf("\n\n\n");
	char *s;
	s = strnstr(in, searchingFor, -1)
	printf("%s\n", s);
	printf("%s\n", ft_strnstr(in, searchingFor, -1));

	const char *largestring = "aaabcabcd";
//	const char *smallstring = "aabc";
	char *ptr;

	ptr = strnstr(largestring, "a", -1);
	printf("%s\n", ptr);
	ptr = ft_strnstr(largestring, "a", -1);
	printf("%s\n", ptr);

    return (0);
}*/
