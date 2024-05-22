/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_calc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 00:29:04 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 14:38:46 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// calculates the distance between two points.
// (using 'Euclidean distance formula')
double	cub_calc_distance_between_points(double x1, double y1, double x2, \
	double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

// checks if a given point is inside a wall based on the map.
int	cub_is_wall(t_mlx *mlx, int x, int y)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = x / BLOCK_SIZE;
	map_grid_y = y / BLOCK_SIZE;
	if (map_grid_x < 0 || map_grid_y < 0 || map_grid_y >= mlx->map->height)
		return (1);
	if (map_grid_x >= mlx->map->row_lengths[map_grid_y])
		return (1);
	if (mlx->map->field[map_grid_y][map_grid_x] == '1')
		return (1);
	return (0);
}

// uses the closest intersection distance to calculate the height of the wall.
// also counters the fish-eye effect by adjusting the distance based on
// the angle difference from the player's view direction/FOV.
void	cub_calculate_wall_position_and_height(t_mlx *mlx, t_ray *ray)
{
	ray->texture = cub_select_texture(mlx, ray, ray->horz_hit_distance, \
		ray->vert_hit_distance);
	ray->perp_distance = cub_min(ray->horz_hit_distance, \
		ray->vert_hit_distance) * cos(ray->ray_angle - mlx->player->angle);
	if (ray->perp_distance > 0)
		ray->wall_slice_height = (BLOCK_SIZE / ray->perp_distance) \
			* ray->distance_to_proj_plane;
	else
		ray->wall_slice_height = SCREEN_HEIGHT;
	ray->draw_start = cub_max(0, SCREEN_HEIGHT / 2 - \
		(int)(ray->wall_slice_height / 2));
	ray->draw_end = cub_min(SCREEN_HEIGHT - 1, SCREEN_HEIGHT / 2 \
		+ (ray->wall_slice_height / 2));
	if (ray->vert_hit_distance < ray->horz_hit_distance)
		ray->wall_hit_pos = ray->vert_hit_y;
	else
		ray->wall_hit_pos = ray->horz_hit_x;
}
