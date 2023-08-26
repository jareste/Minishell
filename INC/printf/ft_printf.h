/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:46:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 20:13:48 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

int	ft_print_decimal(int fd, int n);
int	ft_print_uinteger(int fd, unsigned int n);
int	ft_print_string(int fd, char *str);
int	ft_printf(int fd, const char *s, ...);
int	ft_print_ptr(int fd, void *ptr);
int	ft_print_hex(int fd, unsigned long int n, char format, int c_printed);
int	ft_print_char_fd(int c, int fd);

#endif
