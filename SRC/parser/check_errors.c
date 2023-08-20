/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:56:44 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/20 20:37:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	is_rd(char ch)
{
	if (ch == '<' || ch == '>')
		return (1);
	return (0);
}

static int	check_redirect_in(char *str, int i)
{
	if (!str[i + 1])
		return (1);
	if (i < 1)
		return (0);
	if (is_rd(str[i - 2]) && is_rd(str[i - 1]) && is_rd(str[i]))
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}

static int	check_pipe(char *str, int i)
{
	if (i == 0)
		return (1);
	if (!str[i + 1])
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '<')
		return (1);
	return (0);
}

int	check_input(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		if (str[i] == '>')
			if (check_redirect_in(str, i))
				error = ft_printf(2, "syntax error near unexpected token '>'\n");
		if (str[i] == '|' )
			if (check_pipe(str, i))
				error = ft_printf(2, "syntax error near unexpected token '|'\n");
		if (str[i] == '<')
			if (check_redirect_in(str, i))
				error = ft_printf(2, "syntax error near unexpected token '<'\n");
		if (error != 0)
			return (1);
		i++;
	}
	return (0);
}
