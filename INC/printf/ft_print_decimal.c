/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:24:21 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 20:12:39 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_decimal(int fd, int n)
{
	char	*num;
	int		c_printed;

	c_printed = 0;
	num = ft_itoa(n);
	if (!num)
		return (-1);
	c_printed = ft_print_string(fd, num);
	if (c_printed == -1)
	{
		free(num);
		return (-1);
	}
	free(num);
	return (c_printed);
}
