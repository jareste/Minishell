/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:17:41 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/26 22:18:27 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

static int	open_hdc(t_tokens *exp_tok, char *str, int i)
{
	int		temp_pipe[2];
	char	*line;

	if (pipe(temp_pipe) < 0)
	{
		perror(str);
		return (1);
	}
	else
	{
		while (1)
		{
			line = readline("heredoc> ");
			if (ft_strcmp(line, str) == 0)
				break ;
			ft_printf(temp_pipe[1], "%s\n", line);
			free(line);
		}
	}
	close(temp_pipe[1]);
	exp_tok->words[i]->hd_fd = temp_pipe[0];
	return (0);
}

int	do_hdc(t_tokens *exp_tok)
{
	size_t	i;
	int		type;

	i = 0;
	while (i < exp_tok->size)
	{
		type = exp_tok->words[i]->type;
		if (type == HEREDOC || type == HEREDOCPIPE)
			if (open_hdc(exp_tok, exp_tok->words[i]->word, i))
				return (1);
		i++;
	}
	return (0);
}
