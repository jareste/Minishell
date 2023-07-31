/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:59:32 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 23:59:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 1;
	while (n-- && i++)
		if (((char *)s1)[i - 2] != ((char *)s2)[i - 2])
			return (((unsigned char *)s1)[i - 2]
				- ((unsigned char *)s2)[i - 2]);
	return (0);
}
/*


#include <string.h>
#include <stdio.h>
int main(void)
{
	char c[60] = "ab";
	char b[50] = "adc";

	printf("%d\n", memcmp(c, b, 1));
	printf("%d\n", ft_memcmp(c, b, 1));

	char s[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	
	printf("%d\n", memcmp(s, s2, 1));
	printf("%d\n", ft_memcmp(s, s2, 1));

	printf("%d\n", memcmp(s, s2, 1));
	printf("%d\n", ft_memcmp(s, s2, 1));
	
	return 0;
}*/
