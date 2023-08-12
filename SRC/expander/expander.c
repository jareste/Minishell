/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 00:53:54 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	dst_tobreak(t_word *words)
{
	int		i;
	char	*str;

	i = 0;
	str = words->word;
	while (str[i] && str[i] != ' ' && str[i] != '<' && \
	str[i] != '>' && str[i] != '|')
		i++;
	return (i);
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

static char	*merge_matrix(char **matrix)
{
	char	*str;
	int		i;
	char	*ret;

	i = 0;
	str = "\0";
	ret = "\0";
	while (matrix[i])
	{
		if (i > 0)
		{
			str = ft_strdup(ret);
			free(ret);
		}
		ret = ft_strjoin(str, matrix[i]);
		if (i > 0)
			free(str);
		i++;
	}
	return (ret);
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
		len = dst_tobreak(tokens->words[i]);
		str = ft_calloc(len + 1, sizeof(char *));
		j = 0;
		while (!is_break_exp(tokens->words[i]->word[0]))
		{
			str[j] = ft_strdup(tokens->words[i]->word);
			j++;
			i++;
			if (tokens->size == i)
				break ;
		}
		src = merge_matrix(str);
		printf("return::::%s\n", src);
		new_tokens(exp_tok, src);
		ft_free(str);


		// while (!is_break_exp(str[0][0]))
		// {
		// 	type = tokens->words[i]->type;
		// 	if (type == 1)
		// 		// msh_add_word(exp_tokens, str, ft_strlen(str), 0);
		// 	if (type == 2)

		// 	i++;
		// 	if (i >= tokens->size)
		// 		break;
		// 	str[0] = tokens->words[i]->word;	
		// }	
			i++;
	}
	msh_mount_matrix(exp_tok);
	return (0);
}
/*
ft_Strdup;
puedo crear una matriz donde primero tengo que contar
la distancia hasta el espacio, despues asignar memoria de la matriz
para luego ir rellenando cada posicion con la string 
expandida correspondiente y finalmente juntar todo en 1 sola.
*/
