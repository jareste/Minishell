/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:17:05 by jareste-          #+#    #+#             */
/*   Updated: 2023/05/08 22:22:11 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*special(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	return (0);
}

char	*get_num(int i, int n)
{
	char	*istr;

	istr = (char *)ft_calloc((i + 1), sizeof(char));
	if (istr == NULL)
		return (0);
	if (n < 0)
	{
		n = -n;
		istr[0] = '-';
	}
	while (--i >= 0 && istr[i] == '\0')
	{
		istr[i] = n % 10 + '0';
		n = n / 10;
	}
	return (istr);
}

char	*ft_itoa(int n)
{
	int		i;
	int		temp;

	temp = n;
	i = 0;
	if (n == -2147483648 || n == 0)
		return (special(n));
	if (n < 0)
		i++;
	while (++i && (temp > 9 || temp < -9))
		temp = temp / 10 ;
	return (get_num(i, n));
}
/*
int main(void)
{
	printf("%s\n", ft_itoa(-10));
	printf("%s\n", ft_itoa(-9874));
	printf("%s\n", ft_itoa(8124));
	printf("%s\n", ft_itoa(8));
	return (0);


}*/
