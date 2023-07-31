/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 00:31:17 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/07 00:19:48 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*new_line(char *buffer);
char	*ft_find_line(int fd, char *buffer);
char	*ft_strjoingnl(char const *s1, char const *s2);
char	*ft_strchrgnl(const char *string, int searchedChar );
void	ft_bzerognl(void *s, size_t n);
void	*ft_callocgnl(size_t elementCount, size_t elementSize);
size_t	ft_strlengnl(const char *theString);

#endif
