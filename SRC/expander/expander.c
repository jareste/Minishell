/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 01:23:25 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/09 04:35:54 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	expand_str(t_tokens *tokens, t_tokens *exp_tok, int i)
{
	char	*str;
		
	str = tokens->words[i]->word;
	if (str[0] == ' ' && !str[1])
		return (i + 1);
	msh_add_word(exp_tok, str, ft_strlen(str), 0);
	return (i + 1);
}


int	expander(t_tokens *tokens, t_tokens *exp_tok)
{
	int		i;
	int		type;

	i = 0;
	// printf("%s\n", getenv("HOME"));
	while (tokens->words[i])
	{
		printf("i::::%i\n", i);
		type = tokens->words[i]->type;
		if (type == 3)
			i = expand_break(tokens, exp_tok, i);
		// if (type == 2 || type == 1)
		// 	i = expand_dots(tokens, exp_tok, i);
		else
			i = expand_str(tokens, exp_tok, i);
		printf("ia::::%i\n", i);
	
	}
	msh_mount_matrix(exp_tok);
	return (0);
}
