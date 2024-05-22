/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 13:52:50 by tvan-bee      #+#    #+#                 */
/*   Updated: 2024/05/22 11:51:51 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

# include "../../inc/cub3d.h"

char	*get_next_line(int fd);

char	*ft_gnl_strchr(char *s, char c);
int		ft_gnl_strlen(const char *s);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_substr(char *s, size_t len);

#endif
