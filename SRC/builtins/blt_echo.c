/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 02:00:50 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/18 07:00:02 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	blt_echo(int argc, char **argv)
{
	int	i;
	int	first;

	first = 1;
	if (argc == 1) // Si es sols 1 arg, hem de imprimir un \n;
	{
		ft_printf(1, "\n");//al ft_printf haura d'anar el fd, atm es queda 1.
		return (0);
	}
	i = 1; //mateix que abaix, he canviat la teva condicio per strncmp.
	while (i < argc && ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
		i++;
// a aquest while tenies el mateix problema, si et passaben
// -na o lo que fos, se ho tragaba, quan sols volem -n
	while (i < argc)
	{
		if (!first) // lo que tenies aqui no funcionaba mai pq first era == 1 i no entraba
			ft_printf(1, " ");//al ft_printf haura d'anar el fd, atm es queda 1.
		if (argv[i] == NULL)
			break ;
		ft_printf(1, "%s", argv[i]);//al ft_printf haura d'anar el fd, atm es queda 1.
		first = 0;//despres de escriure el primer cop first = 0 aleshores printeja espais
		i++;
	}
	if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) != 0)
		ft_printf(1, "\n");//al ft_printf haura d'anar el fd, atm es queda 1.
	return (0);
}

// int main(int ac, char **av)
// {
// 	blt_echo(ac, av);
// 	return 0;

// }
