/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 03:23:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/08/19 03:25:06 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	blt_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (ft_printf(1, "%s\n", pwd) == -1)
	{
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}
