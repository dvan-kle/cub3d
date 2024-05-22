/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_setup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 12:20:59 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 14:38:18 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// void	cub_print_modified_map(t_check_map *check_map)
// {
// 	int	i;

// 	i = 0;
// 	while (i < check_map->height)
// 	{
// 		printf("%s\n", check_map->field[i]);
// 		i++;
// 	}
// }
// cub_print_modified_map(check_map);

void	cub_map_save_row_lengths(t_map *map)
{
	int	i;

	map->row_lengths = (int *)allocate_memory(sizeof(int) * map->height);
	i = 0;
	while (i < map->height)
	{
		map->row_lengths[i] = ft_strlen(map->field[i]);
		i++;
	}
}

void	cub_set_mods(t_map *map, t_check_map *check_map)
{
	int		longest_line ;
	int		i;
	int		length;
	char	*line;

	longest_line = 0;
	i = 0;
	while (i < map->height)
	{
		line = map->field[i];
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		length = ft_strlen(line);
		if (length > longest_line)
			longest_line = length;
		i++;
	}
	check_map->width = longest_line + 2;
	check_map->height = map->height + 2;
}

void	cub_place_dots(t_map *map, t_check_map *check_map, int i)
{
	int	j;

	while (i < map->height)
	{
		check_map->field[i + 1] = ft_calloc(check_map->width + 1, sizeof(char));
		check_map->field[i + 1][0] = '.';
		j = 0;
		while (j < (int)ft_strlen(map->field[i]))
		{
			if (map->field[i][j] == ' ')
				check_map->field[i + 1][j + 1] = '.';
			else
				check_map->field[i + 1][j + 1] = map->field[i][j];
			j++;
		}
		j = (ft_strlen(map->field[i]) + 1);
		while (j < check_map->width - 1)
		{
			check_map->field[i + 1][j] = '.';
			j++;
		}
		check_map->field[i + 1][check_map->width - 1] = '.';
		i++;
	}
}

void	cub_set_dots(t_map *map, t_check_map *check_map)
{
	check_map->field[0] = (char *)ft_calloc(check_map->width + 1, sizeof(char));
	ft_memset(check_map->field[0], '.', check_map->width);
	cub_place_dots(map, check_map, 0);
	check_map->field[check_map->height - 1] = \
		(char *)ft_calloc(check_map->width + 1, sizeof(char));
	ft_memset(check_map->field[check_map->height - 1], '.', check_map->width);
}

int	cub_setup_map_checks(t_map *map, t_check_map *check_map)
{
	cub_set_mods(map, check_map);
	check_map->field = (char **)allocate_memory(sizeof(char *)
			* check_map->height);
	cub_set_dots(map, check_map);
	return (0);
}
