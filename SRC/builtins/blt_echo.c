/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 02:00:50 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/23 19:19:47 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	is_n(char *str)
{
	int	i;

	i = 2;
	if (ft_strlen(str) > 1)
	{
		if (str[0] == '-' && str[1] == 'n')
			while (str[i])
			{
				if (str[i] == 'n')
					i++;
				else
					return (0);
			}
			else
				return (0);
	}
	else
		return (0);
	return (1);
}

int	blt_echo(int argc, char **argv)
{
	int	i;
	int	first;

	ft_printf(2, "echo:::::::::::::::::::::::::::::::::::::::;%s\n", argv[1]);
	first = 1;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	i = 1;
	while (i < argc && is_n(argv[i]))
		i++;
	// printf("i::::%i, argc:::::%i\n", i, argc);
	while (i < argc)
	{
		if (!first)
			ft_printf(1, " ");
		if (argv[i] == NULL)
			break ;
		printf("%s", argv[i]);
		first = 0;
		i++;
	}
	if (!is_n(argv[1]))
		printf("\n");
	return (0);
}

// int main(int ac, char **av)
// {
// 	blt_echo(ac, av);
// 	return 0;

// }
