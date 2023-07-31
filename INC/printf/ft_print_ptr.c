/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:45:20 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/31 08:57:08 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(void *ptr)
{
	int	c_printed;
	int	aux;

	if (ft_print_string("0x") == -1)
		return (-1);
	c_printed = 2;
	aux = ft_print_hex((unsigned long)ptr, 'x', 0);
	if (aux == -1)
		return (-1);
	c_printed += aux;
	return (c_printed);
}
