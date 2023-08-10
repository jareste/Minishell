/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 20:33:57 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	dst_tobreak(t_word **words)
{
	int		i;
	char	*str;

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

int	expander(t_tokens *tokens, t_tokens *exp_tok)
{
	size_t		i;
	int			type;
	char		*str[2];

	i = 0;
	type = 0;
	while (i < tokens->size)
	{
		str[0] = tokens->words[i]->word;
		while (!is_break_exp(str[0]))
		{
			type = tokens->words[i]->type;
			if (type == 1)
				// msh_add_word(exp_tokens, str, ft_strlen(str), 0);
			

			i++;
			if (i >= tokens->size)
				break;
			str[0] = tokens->words[i]->word;	
		}	
	}
	msh_mount_matrix(exp_tok);
	return (0);
}
