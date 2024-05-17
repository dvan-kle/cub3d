/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_initialization_utils.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:51:31 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/17 12:47:01 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_map	*cub_init_map_and_open_file(char *file, int *fd)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	*fd = open(file, O_RDONLY);
	if (!map || *fd < 0)
		cub_error(1, "Error: Initialization or File Opening Failed.\n");
	return (map);
}

void	cub_allocate_map_field(t_map *map)
{
	map->field = ft_calloc(1, sizeof(char *));
	if (!map->field)
		cub_error(1, "Error: Memory allocation failed for map field.\n");
}

void	free_map_ids(t_map *map)
{
	free(map->id_no);
	free(map->id_so);
	free(map->id_we);
	free(map->id_ea);
	free(map->id_f);
	free(map->id_c);
}

void	cub_finalize_map(t_map *map, int height, int max_width)
{
	map->north_texture = mlx_load_png(map->id_no);
	map->south_texture = mlx_load_png(map->id_so);
	map->west_texture = mlx_load_png(map->id_we);
	map->east_texture = mlx_load_png(map->id_ea);
	map->color_ceiling = cub_parse_rgb_string_to_hex(map->id_c);
	map->color_floor = cub_parse_rgb_string_to_hex(map->id_f);
	map->field[height] = NULL;
	map->height = height;
	map->width = max_width;
	free_map_ids(map);
}
