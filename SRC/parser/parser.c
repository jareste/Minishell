/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:21:40 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/06 13:33:19 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	do_break(t_tokens *tokens, char *str)
{
	msh_add_word(tokens, str, 1, 0);
	return (1);
}

static int	check_normal_ch(char ch)
{
	if (break_ch(ch) || ch == '#' || ch == '"' \
	|| ch == ' ' || ch == '\'')
		return (1);
	return (0);
}

static int	do_string(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] && !check_normal_ch(str[i]))
		i++;
	msh_add_word(tokens, str, i, 0);
	return (i);
}

static int	parse_string(t_tokens *tokens, char *str)
{
	int	i;
	int	j;

	j = 0; 
	i = 0;
	while (str[i] && str[i] != '#')
	{
		if (break_ch(str[i]))
			i += do_break(tokens, str + i);
		else if (str[i] == '"' || str[i] == '\'')
			i += do_dots(tokens, str + i);
		else if (str[i] == ' ')
			i += do_spaces(tokens, str + i);
		else
			i += do_string(tokens, str + i);
		j++;
	}
	return (0);
}

int	parser(t_tokens *tokens)
{
	tokens->str = readline("bobo> ");
	if (!tokens->str)
		return (-1);
	parse_string(tokens, tokens->str);
	add_history(tokens->str);
	msh_mount_matrix(tokens);
	return (0);
}
