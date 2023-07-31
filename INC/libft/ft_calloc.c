/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:18:37 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/09 00:15:26 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/*
#include <stdio.h>

int main(void)
{
	int *ptr;
	int n, i;

	n = 42 * 3;
	ptr = (int *)calloc(n, sizeof(int));

	i = 0;

	while (i < n)
	{
		ptr[i] = i + 1;
		printf("%d, ", ptr[i]);
		i++;
	}
	ptr = (int *)ft_calloc(n, sizeof(int));
	  i = 0;

                printf("\n\n");
        while (i < n)
        {
                ptr[i] = i + 1;
                printf("%d, ", ptr[i]);
                i++;
        }

	return(0);
}*/
