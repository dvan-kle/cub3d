/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_load_values.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 12:02:26 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/17 15:50:50 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cub_set_player_start_position(t_mlx *mlx)
{
	mlx->player->pixel_x = mlx->map->player_start_x * BLOCK_SIZE \
		+ (BLOCK_SIZE / 2);
	mlx->player->pixel_y = mlx->map->player_start_y * BLOCK_SIZE \
		+ (BLOCK_SIZE / 2);
	if (mlx->player->direction == 'N')
		mlx->player->angle = 3 * M_PI / 2;
	if (mlx->player->direction == 'E')
		mlx->player->angle = 0;
	if (mlx->player->direction == 'S')
		mlx->player->angle = M_PI / 2;
	if (mlx->player->direction == 'W')
		mlx->player->angle = M_PI;
}

t_map	*cub_load_map_values(char *file)
{
	int		fd;
	int		fd2;
	int		start_map;
	t_map	*map;

	start_map = 0;
	map = cub_init_map_and_open_file(file, &fd, &fd2);
	cub_process_lines(fd, map, &start_map);
	cub_fill_map(fd2, map, start_map);
	close(fd);
	close(fd2);
	cub_finalize_map(map);
	return (map);
}
