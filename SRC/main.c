/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:24:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/02 22:48:21 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

int	main(int argc, char **argv, char *env[])
{
	argc = 0;
	argv = 0;
	env = 0;
	t_tokens	tokens;

	while (1)
	{
		tokens.str = readline("hola> ");
		if (tokens.str[0] != '\0')
			parser(tokens.str, &tokens);
		add_history(tokens.str);
		free(tokens.str);
	}


	return 0;
	
}
