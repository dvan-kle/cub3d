/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_processing_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:52:36 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/24 11:01:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cub_store_identifier_value(char *line, t_map *map)
{
	char	*new_line;

	new_line = cub_trim_first_whitespace(line);
	if (ft_strncmp(new_line, "NO", 2) == 0)
		cub_assign_and_check(new_line, &(map->id_no));
	else if (ft_strncmp(new_line, "SO", 2) == 0)
		cub_assign_and_check(new_line, &(map->id_so));
	else if (ft_strncmp(new_line, "WE", 2) == 0)
		cub_assign_and_check(new_line, &(map->id_we));
	else if (ft_strncmp(new_line, "EA", 2) == 0)
		cub_assign_and_check(new_line, &(map->id_ea));
	else if (ft_strncmp(new_line, "F", 1) == 0)
		cub_assign_and_check(new_line, &(map->id_f));
	else if (ft_strncmp(new_line, "C", 1) == 0)
		cub_assign_and_check(new_line, &(map->id_c));
	else
	{
		if (cub_check_empty_line(new_line) == 1)
		{
			free(new_line);
			cub_error(1, "Error\nInvalid identifier.\n");
		}
	}
	free(new_line);
}

void	cub_line(t_map *map, char *line, int *start_map, int i)
{
	if (*start_map == 0)
		*start_map = i;
	if ((int)ft_strlen(line) > map->width)
		map->width = (int)ft_strlen(line);
	map->height++;
	free(line);
}

void	cub_process_lines(int fd, t_map *map, int *start_map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->id_no && map->id_so && map->id_we && map->id_ea
			&& map->id_f && map->id_c)
			cub_line(map, line, start_map, i);
		else
		{
			cub_store_identifier_value(line, map);
			free(line);
		}
		line = get_next_line(fd);
		i++;
	}
	if (!map->id_no || !map->id_so || !map->id_we || !map->id_ea
		|| !map->id_f || !map->id_c)
		cub_error(1, "Error\nMap missing one or more identifier.\n");
}

void	cub_fill_map(int fd, t_map *map, int start_map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = get_next_line(fd);
	map->field = allocate_memory(sizeof(char *) * (map->height + 1));
	if (map->height == 0)
		cub_error(1, "Error\nMap is empty.\n");
	while (line)
	{
		if (j >= start_map)
		{
			map->field[i] = line;
			i++;
		}
		else
			free(line);
		line = get_next_line(fd);
		j++;
	}
	map->field[i] = NULL;
}
