/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:21:40 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/02 23:29:32 by jareste-         ###   ########.fr       */
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
	int	flag;

	i = 0;
	flag = 0;
	cw = 0;
	while (str[i] && str[i]!= '#')
	{
		if (break_ch(str[i]))
			i++;
		else if (str[i] == '"')
		{
			if (flag == 0)
			{
				i++;
				flag = 1;
			}
			if (flag == 1)
				flag = 0;
			while (str[i] && str[i] != '"' && !break_ch(str[i]) && flag == 1)
				i++;
		}
		else if (str[i] && str[i] == '\'')
			while (str[i] && str[i] != '\'' && !break_ch(str[i]))
				i++;
		else if (str[i] && str[i]!= ' ')
			while (str[i] && str[i] != ' ' && !break_ch(str[i]))
				i++;
		if (str[i] && str[i]!= '#' && !break_ch(str[i]))
			i++;
		if (flag == 0)
			cw++;
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
	if (flag == 1)
		return (j - i - flag - 1);
	return (j - i);
}

static int	cp_word(t_tokens *tokens, int j, int len, int i)
{
	int	k;
	int	flag;

	k = 0;
	flag = 0;
	if (tokens->str[j] == '"' || tokens->str[j] == '\'')
	{
		if (tokens->str[j] == '"')
			flag = 2;
		else
			flag = 1;
		j++;
	}
	tokens->words[i].word = malloc(sizeof(char) * len + 1);
	tokens->words[i].word[len] = '\0';
	while (len > 0)
	{
		tokens->words[i].word[k++] = tokens->str[j++];
		len--;
	}
	return (flag);
}

void	parser(char	*str, t_tokens	*tokens) //vull separar cada token per enviar i guardarlo correcctament, si te cometes el token he d'enviar un int.
{
	int	cw;
	int	i;
	int	j;
	int wl;

	cw = count_tokens(str);
	printf("cw%i\n",cw);
	tokens->words = malloc((cw) * sizeof(t_word));
	i = 0;
	j = 0;
	while (i < cw)
	{
		tokens->words[i].dot = 0;
		while (tokens->str[j] == ' ')
			j++;
		wl = word_len(tokens->str, j);
		printf("WL::%i\n", wl);
		tokens->words[i].dot = cp_word(tokens, j, wl, i);
		printf("str::::     %s\n",tokens->words[i].word);
		j += wl;
		printf("dot:::%i\n", tokens->words[i].dot);
		if (tokens->words[i].dot != 0)
			j += 2;
		i++;
	}
}
