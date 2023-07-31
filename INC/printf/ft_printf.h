/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:46:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/31 09:13:07 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

int	ft_print_decimal(int n);
int	ft_print_uinteger(unsigned int n);
int	ft_print_string(char *str);
int	ft_printf(const char *s, ...);
int	ft_print_ptr(void *ptr);
int	ft_print_hex(unsigned long int n, char format, int c_printed);
int	ft_print_char_fd(int c, int fd);

#endif
