/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 09:20:40 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	dst_tobreak(t_tokens *tokens, size_t i)
{
	int		j;
	char	*str;

	j = 0;
	str = tokens->words[i]->word;
	while (str[0] && str[0] != ' ' && str[0] != '<' && \
	str[0] != '>' && str[0] != '|')
	{
		j++;
		i++;
		if (tokens->size <= i)
			break ;
		str = tokens->words[i]->word;
	}
	return (j);
}

static int	is_break_exp(char ch)
{
	if (ch == ' ' || ch == '<' || ch == '>' || ch == '|')
		return (1);
	return (0);
}

static	void	ft_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static void	new_tokens(t_tokens *exp_tok, char *str)
{
	msh_add_word(exp_tok, str, ft_strlen(str), 0);
	free(str);
}

int	expander(t_tokens *tokens, t_tokens *exp_tok)
{
	size_t		i;
	size_t		j;
	int			len;
	char		**str;
	char		*src;

	i = 0;
	while (i < tokens->size)
	{
		len = dst_tobreak(tokens, i);
		str = ft_calloc(len + 1, sizeof(char *));
		j = 0;
		while (!is_break_exp(tokens->words[i]->word[0]))
		{
			if (tokens->words[i]->type == 2)
				str[j] = expand_dots(tokens, i, 0);
			else if (tokens->words[i]->type == 3)
			{
				str[j] = ft_strdup(expand_dollar(tokens, i));
				i++;
			}
			else
				str[j] = ft_strdup(tokens->words[i]->word);
			j++;
			i++;
			if (tokens->size == i)
				break ;
		}
		src = merge_matrix(str);
		new_tokens(exp_tok, src);
		ft_free(str);
		i++;
	}
	msh_mount_matrix(exp_tok);
	return (0);
}
/*
puedo crear una matriz donde primero tengo que contar
la distancia hasta el espacio, despues asignar memoria de la matriz
para luego ir rellenando cada posicion con la string 
expandida correspondiente y finalmente juntar todo en 1 sola.
*/
