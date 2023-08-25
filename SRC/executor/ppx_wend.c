/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_wend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:42:15 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/09 15:42:16 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

size_t	ppx_findwend(char *args_cpy, size_t *i, size_t *end)
{
	int	ok;

	ok = 1;
	while (args_cpy[*end] && args_cpy[*end] != ' ')
	{
		if (args_cpy[*end] == 92)
			ppx_wnd_backslash(args_cpy, i, end);
		else if (args_cpy[*end] == 39)
			ok = ppx_wnd_1quote(args_cpy, i, end);
		else if (args_cpy[*end] == '"')
			ok = ppx_wnd_2quotes(args_cpy, i, end);
		else
		{
			args_cpy[*i] = args_cpy[*end];
			*i = *i + 1;
		}
		if (ok != 1)
			return (ok);
		*end = *end + 1;
	}
	ppx_wnd_putnull(args_cpy, i, end);
	return (*i);
}

void	ppx_wnd_backslash(char *args_cpy, size_t *i, size_t *end)
{
	*end = *end + 1;
	args_cpy[*i] = args_cpy[*end];
	*i = *i + 1;
}

int	ppx_wnd_1quote(char *args_cpy, size_t *i, size_t *end)
{
	*end = *end + 1;
	while (args_cpy[*end] && args_cpy[*end] != 39)
	{
		args_cpy[*i] = args_cpy[*end];
		*i = *i + 1;
		*end = *end + 1;
	}
	if (args_cpy[*end] != 39)
		return (0);
	return (1);
}

int	ppx_wnd_2quotes(char *args_cpy, size_t *i, size_t *end)
{
	*end = *end + 1;
	while (args_cpy[*end] && args_cpy[*end] != '"')
	{
		if (args_cpy[*end] == 92)
		{
			*end = *end + 1;
			args_cpy[*i] = args_cpy[*end];
			*i = *i + 1;
		}
		else
		{
			args_cpy[*i] = args_cpy[*end];
			*i = *i + 1;
		}
		*end = *end + 1;
	}
	if (args_cpy[*end] != '"')
		return (0);
	return (1);
}

void	ppx_wnd_putnull(char *args_cpy, size_t *i, size_t *end)
{
	if (args_cpy[*end])
	{
		args_cpy[*i] = '\0';
		*end = *end + 1;
		*i = *i + 1;
	}
	else
		args_cpy[*i] = '\0';
}
