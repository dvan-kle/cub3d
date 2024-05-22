/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 13:52:34 by tvan-bee      #+#    #+#                 */
/*   Updated: 2024/05/22 11:51:05 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_set_buffer(char *buffer)
{
	char	*new_buffer;

	if (!ft_gnl_strchr(buffer, '\n'))
		return (free(buffer), NULL);
	new_buffer = ft_gnl_substr((ft_gnl_strchr(buffer, '\n') + 1),
			ft_gnl_strlen(ft_gnl_strchr(buffer, '\n')));
	return (free(buffer), new_buffer);
}

static char	*ft_get_line(char *buffer)
{
	int		len;
	char	*line;

	if (!*buffer)
		return (NULL);
	if (ft_gnl_strchr(buffer, '\n'))
		len = ((ft_gnl_strlen(buffer)
					- ft_gnl_strlen(ft_gnl_strchr(buffer, '\n'))) + 1);
	else
		len = ft_gnl_strlen(buffer);
	line = ft_gnl_substr(buffer, len);
	if (!line)
		return (free(buffer), NULL);
	return (line);
}

static char	*ft_read_file(int fd, char *buffer)
{
	char	*new_buffer;
	int		bytes;

	new_buffer = (char *)allocate_memory(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_buffer)
		return (free(buffer), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, new_buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(new_buffer);
			free(buffer);
			return (NULL);
		}
		new_buffer[bytes] = '\0';
		buffer = ft_gnl_strjoin(buffer, new_buffer);
		if (!buffer)
			return (free(new_buffer), NULL);
		if (ft_gnl_strchr(buffer, '\n'))
			break ;
	}
	free(new_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_set_buffer(buffer);
	return (line);
}
