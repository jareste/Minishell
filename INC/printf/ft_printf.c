/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:13 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/14 22:48:00 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_format(int fd, char format, va_list args)
{
	int	c_printed;

	c_printed = 0;
	if (format == 'c')
		c_printed = ft_print_char_fd(va_arg(args, int), fd);
	else if (format == 's')
		c_printed = ft_print_string(fd ,va_arg(args, char *));
	else if (format == 'p')
		c_printed = ft_print_ptr(fd ,va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		c_printed = ft_print_decimal(fd ,va_arg(args, int));
	else if (format == 'u')
		c_printed = ft_print_uinteger(fd ,va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		c_printed = ft_print_hex(fd, va_arg(args, unsigned int), format, 0);
	else if (format == '%')
	{
		c_printed = ft_print_char_fd('%', fd);
	}
	else
		return (-1);
	return (c_printed);
}

int	bucle(int fd, const char *s, va_list args, int c_printed)
{
	int	i;
	int	aux;

	i = 0;
	while (s[i])
	{
		aux = 0;
		if (s[i] == '%')
		{
			aux = ft_check_format(fd, s[i + 1], args);
			if (aux == -1)
				return (-1);
			c_printed += aux;
			i++;
		}
		else
		{
			if (ft_print_char_fd(s[i], fd) == -1)
				return (-1);
			c_printed++;
		}
		i++;
	}
	return (c_printed);
}

#include <stdio.h>

int	ft_printf(int fd, const char *s, ...)
{
	va_list	args;
	int		c_printed;

	c_printed = 0;
	va_start(args, s);
	c_printed = bucle(fd, s, args, c_printed);
	va_end(args);
	printf("::::::%i\n", fd);
	return (c_printed);
}
/*
#include <stdio.h>
int	main(void)
{
//	char a = 'a';
//	char *b = "muchas gracias";
//	unsigned int c = 4294967295;
	int dfs;
//	void *s = "holaquetal";
//	unsigned int x = 636321;

//	ft_print_decimal(a);
//	printf("\n\n\n\n\n");
	dfs = ft_printf("%d", 0);
	ft_printf("      %i", dfs);
	printf("\n\n\n");
	dfs = printf("%d", 0);
	printf("      %i", dfs);
	return (0);

}*/
