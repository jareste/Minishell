/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:24:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/02 11:23:54 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

int	main(int argc, char **argv, char *env[])
{
	argc = 0;
	argv = 0;
	env = 0;

	// int i;
	char *line;
	while (1)
	{
		line = readline("hola> ");
		parser(line);

		// i = 0;
		// while (line[i] != '\0' && line[i] != '#')
		// 	i++;
		// if (ft_strncmp("exit", line, 5) == 0)
		// 	exit (1);
		// else if (line[i] == '\0')
		// 	ft_printf("    final de linea\n %i\n",ft_strncmp("exit", line, 5));
		// else if (line[i] == '#')
		// 	ft_printf("        comentario\n");
		add_history(line);
		free(line);
	}


	return 0;
	
}
