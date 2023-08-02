/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:21:40 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/02 22:52:21 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

static int	break_ch(char c)
{
	if (c == '$' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);

}

static int	count_tokens(char *str)
{
	int	i;
	int	cw;

	i = 0;
	cw = 0;
	while (str[i] && str[i]!= '#')
	{
		if (break_ch(str[i]))
			i++;
		else if (str[i] == '"')
			while (str[i] && str[i] != '"' && !break_ch(str[i]))
				i++;
		else if (str[i] && str[i] == '\'')
			while (str[i] && str[i] != '\'' && !break_ch(str[i]))
				i++;
		else if (str[i] && str[i]!= ' ')
			while (str[i] && str[i] != ' ' && !break_ch(str[i]))
				i++;
		cw++;
		if (str[i] && str[i]!= '#' && !break_ch(str[i]))
			i++;
	}
	return (cw);
}

static	int	word_len(char *str, int i)
{
	int	j;
	int	flag;

	j = i;
	flag = 0;
	while (str[j] && str[j]!= '#' && str[j] != ' ' && !break_ch(str[j]))
	{
		// printf("aqui entro bien\n");

		if (break_ch(str[j]))
			j++;
		else if (str[j] == '"' && flag == 0)
		{
			j++;
			flag = 1;
			while (str[j] && str[j] != '"' && !break_ch(str[j]))
				j++;
		}
		else if (str[j] && str[j] == '\'')
			while (str[j] && str[j] != '\'' && !break_ch(str[j]))
				j++;
		else if (str[j] && str[j]!= ' ')
			while (str[j] && str[j] != ' ' && !break_ch(str[j]))
				j++;
	}
	if (break_ch(str[j]) && (j - i) == 0)
		return (1);
	return (j - i - flag);
}

static void	cp_word(t_tokens *tokens, int j, int len, int i)
{
	int	k;
	int	flag;

	k = 0;
	flag = 0;
	printf("len::%i\n", len);
	if (tokens->str[j] == '"' || tokens->str[j] == '\'')
	{
		j++;
		len-=2;
	}
	tokens->words[i].word = malloc(sizeof(char) * len + 1);
	tokens->words[i].word[len] = '\0';
	
	while (len > 0)
	{
		tokens->words[i].word[k++] = tokens->str[j++];
		len--;
	}
}

void	parser(char	*str, t_tokens	*tokens) //vull separar cada token per enviar i guardarlo correcctament, si te cometes el token he d'enviar un int.
{
	int	cw;
	int	i;
	int	j;

	cw = count_tokens(str);
	tokens->words = malloc((cw) * sizeof(t_word));
	i = 0;
	j = 0;
	while (i < cw)
	{
		while (tokens->str[j] == ' ')
			j++;
		printf("WL::%i\n", word_len(tokens->str, j));
		cp_word(tokens, j, word_len(tokens->str, j), i);
		printf("str::::     %s\n",tokens->words[i].word);
		i++;
		j += word_len(tokens->str, j);
	}
}
