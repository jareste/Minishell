/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:37:54 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/24 21:57:50 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	dst_todot(char *str, char dot)
{
	int	i;

	i = 1;
	if (str[1] == dot)
		return (-2);
	while (str[i] && str[i] != dot)
		i++;
	if (str[i] == '\0')
	{
		printf("error not closing quotation\n");
		return (-1);
	}
	return (i - 1);
}

int	do_dots(t_tokens *tokens, char *str)
{
	int	len;

	len = dst_todot(str, str[0]);
	if (len == -1 || len == -2)
	{
		tokens->error = 1;
		return (1);
	}
	if (len == 0)
		return (len);
	if (str[0] == '"')
		msh_add_word(tokens, str + 1, len, 2);
	if (str[0] == '\'')
		msh_add_word(tokens, str + 1, len, 1);
	return (len + 2);
}

int	do_spaces(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	msh_add_word(tokens, " ", 1, 4);
	return (i);
}

int	break_ch(char c)
{
	if (c == '$' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
