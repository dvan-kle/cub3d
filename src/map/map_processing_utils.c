/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_processing_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:52:36 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/17 15:48:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*cub_extract_value(char *line)
{
	char	*value_start;

	value_start = ft_strchr(line, ' ');
	if (!value_start)
		return (ft_strdup(""));
	return (cub_trim_whitespace(value_start + 1));
}

void	cub_store_identifier_value(char *line, t_map *map)
{
	char	*new_line;

	new_line = cub_trim_first_whitespace(line);
	if (ft_strncmp(new_line, "NO", 2) == 0)
		map->id_no = cub_extract_value(new_line);
	else if (ft_strncmp(new_line, "SO", 2) == 0)
		map->id_so = cub_extract_value(new_line);
	else if (ft_strncmp(new_line, "WE", 2) == 0)
		map->id_we = cub_extract_value(new_line);
	else if (ft_strncmp(new_line, "EA", 2) == 0)
		map->id_ea = cub_extract_value(new_line);
	else if (ft_strncmp(new_line, "F", 1) == 0)
		map->id_f = cub_extract_value(new_line);
	else if (ft_strncmp(new_line, "C", 1) == 0)
		map->id_c = cub_extract_value(new_line);
	free(new_line);
}

void	cub_process_lines(int fd, t_map *map, int *start_map)
{
	char	*line;
	int		line_length;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->id_no && map->id_so && map->id_we && map->id_ea && map->id_f && map->id_c)
		{
			if (*start_map == 0)
				*start_map = i;
			line_length = ft_strlen(line);
			if (line_length > map->width)
				map->width = line_length;
			map->height++;
			free(line); // Freeing the line as we only count its length
		}
		else
		{
			cub_store_identifier_value(line, map);
			free(line);
		}
		line = get_next_line(fd);
		i++;
	}
	if (!map->id_no || !map->id_so || !map->id_we || !map->id_ea || !map->id_f || !map->id_c)
		cub_error(1, "Error: Map missing one or more identifier.\n");
}


void	cub_fill_map(int fd, t_map *map, int start_map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = get_next_line(fd);
	map->field = malloc(sizeof(char *) * (map->height + 1));
	if (!map->field)
		cub_error(1, "Error: Memory allocation failed for map->field.\n");
	while (line)
	{
		if (j >= start_map)
		{
			map->field[i] = line;
			i++;
		}
		else
		{
			free(line);
		}
		line = get_next_line(fd);
		j++;
	}
	map->field[i] = NULL;
}
