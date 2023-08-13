/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/13 07:42:54 by jareste-         ###   ########.fr       */
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
		printf("hola\n");
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

char	*expand_dollar(t_tokens *tokens, int i)
{
	char	*str;
	int		type;

	type = tokens->words[i + 1]->type;
	if (type == 4)
	{
		str = "$";
		return (str);
	}
	str = tokens->words[i + 1]->word;
	if (!getenv(str))
		return (ft_strdup(""));
		// return (ft_strjoin(tokens->words[i]->word, str));
	return (getenv(str));
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
		printf("len::::%i\n", len);
		while (!is_break_exp(tokens->words[i]->word[0]))
		{
		//en este bucle es donde tengo que expandir antes del merge
		//justo antes del strdup para duplicar ya expandido en el 
		//caso de los $
			if (tokens->words[i]->type == 2)
				str[j] = expand_dots(tokens, i);
			else if (tokens->words[i]->type == 3)
			{
				str[j] = expand_dollar(tokens, i);
				str[j] = ft_strdup(str[j]);
				i++;
			}
			else
				str[j] = ft_strdup(tokens->words[i]->word);
			// printf("%zu, str:::%s\n", j, str[j]);
			j++;
			i++;
			if (tokens->size == i)
				break ;
		}
		printf("1::::%s\n", str[0]);
		printf("2::::%s\n", str[1]);
		printf("j:::%zu\n", j);
		src = merge_matrix(str);
		printf("return::::%s\n", src);
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
