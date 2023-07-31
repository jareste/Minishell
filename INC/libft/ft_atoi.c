/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:24:26 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/06 04:25:12 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	static	ft_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int				i;
	int				final_value;
	long long int	nbr;

	nbr = 0;
	i = 0;
	final_value = 1;
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			final_value = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < -INT_MIN && final_value == -1)
			return (0);
		if (nbr > INT_MAX && final_value == 1)
			return (-1);
	}
	return (nbr * final_value);
}
// static int	ft_isspace(int c)
// {
// 	if (c == ' ' || c == '\n' || c == '	'
// 		|| c == '\t' || c == '\v' || c == '\f' || c == '\r')
// 		return (1);
// 	return (0);
// }

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	neg;
// 	int	result;

// 	i = 0;
// 	result = 0;
// 	neg = 0;
// 	while (ft_isspace(str[i]))
// 		i++;
// 	if (str[i] == '-')
// 	{
// 		neg = 1;
// 		i++;
// 	}
// 	else if (str[i] == '+')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		result = (result * 10) + (str[i] - '0');
// 		i++;
// 	}
// 	if (neg == 1)
// 		return (-result);
// 	return (result);
// }
/*
 
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char b[20] = "		42lyion";


	printf("%d\n", atoi(b));
	printf("%d\n", ft_atoi(b));
}*/
