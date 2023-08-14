/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:15:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/14 22:49:35 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(int fd, unsigned long int n, char format, int c_printed)
{
	char	*basel;
	char	*baseu;

	basel = "0123456789abcdef";
	baseu = "0123456789ABCDEF";
	if (n > 15)
		c_printed = ft_print_hex(fd, n / 16, format, c_printed);
	if (c_printed == -1)
		return (-1);
	if (format == 'x')
	{
		c_printed++;
		if (ft_print_char_fd(basel[n % 16], fd) == -1)
			return (-1);
	}
	if (format == 'X')
	{
		c_printed++;
		if (ft_print_char_fd(baseu[n % 16], fd) == -1)
			return (-1);
	}
	return (c_printed);
}
