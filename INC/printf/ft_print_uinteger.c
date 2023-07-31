/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uinteger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:45:52 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/31 08:57:20 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uinteger(unsigned int n)
{
	char	c;
	size_t	temp;
	int		c_printed;

	c = 0;
	c_printed = 0;
	temp = n;
	while (++c_printed && (temp > 9))
		temp = temp / 10;
	if (n > 9)
	{
		temp = n / 10;
		n = n % 10;
		if (ft_print_decimal(temp) == -1)
			return (-1);
	}
	if (n < 9)
		temp = n;
	c = n + '0';
	if (ft_print_char_fd(c, 1) == -1)
		return (-1);
	return (c_printed);
}
