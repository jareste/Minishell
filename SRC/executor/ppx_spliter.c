/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_spliter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:30:29 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/08/18 13:11:15 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ppx_print_matrix(char **mtrx)
{
	while (*mtrx)
	{
		ft_printf(2, "%s\n", *mtrx);
		mtrx++;
	}
}

char	**ppx_free_matrix(char **mtrx)
{
	if (!mtrx)
		return (NULL);
	free(mtrx[0]);
	free(mtrx);
	return (NULL);
}

char	**ppx_split(char *args)
{
	size_t	start;
	size_t	end;
	char	**result;
	char	*args_cpy;

	result = NULL;
	args_cpy = ft_strdup(args);
	start = 0;
	end = start + 0;
	while (args_cpy[end])
	{
		while (args_cpy[end] == ' ')
		{
			end++;
			if (!args_cpy[end])
				break ;
		}
		result = ppx_ptarg(result, args_cpy, start);
		if (!result)
			return (ppx_free_matrix(result));
		if (!ppx_findwend(args_cpy, &start, &end))
			return (ppx_free_matrix(result));
	}
	return (result);
}

char	**ppx_ptarg(char **result, char *args_cpy, size_t start)
{
	char	**result2;
	size_t	i;

	if (result == NULL)
	{
		result = (char **) malloc(sizeof(char *) * (1));
		if (!result)
			return (0);
		result[0] = NULL; 
	}
	i = 0;
	while (result[i])
		i++;
	result2 = (char **) malloc(sizeof(char *) * (i + 2));
	if (!result2)
		return (0);
	i = -1;
	while (result[++i])
		result2[i] = result[i];
	result2[i++] = args_cpy + start;
	result2[i] = NULL;
	free(result);
	result = result2;
	return (result);
}
