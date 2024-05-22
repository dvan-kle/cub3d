/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_horizontal.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 00:24:32 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 11:47:40 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// initializes step sizes for horizontal ray intersections based on current ray
// direction.
void	cub_init_horz_ray_info(t_ray *ray, t_ray_info *info)
{
	info->ystep = BLOCK_SIZE;
	info->xstep = BLOCK_SIZE / tan(ray->ray_angle);
	if (ray->is_ray_facing_down)
		info->ystep *= 1;
	else
		info->ystep *= -1;
	if (ray->is_ray_facing_right && info->xstep < 0)
		info->xstep *= -1;
	else if (!ray->is_ray_facing_right && info->xstep > 0)
		info->xstep *= -1;
}

// calculates the initial intersection point for the ray's first interaction
// with horizontal grid lines, setting the starting point for checking wall
// collisions.
void	cub_init_horz_intercepts(t_mlx *mlx, t_ray *ray, \
	t_intercept *intercept, t_ray_info *info)
{
	intercept->yintercept = floor(mlx->player->pixel_y / \
		BLOCK_SIZE) * BLOCK_SIZE;
	if (ray->is_ray_facing_down)
		intercept->yintercept += BLOCK_SIZE;
	intercept->xintercept = mlx->player->pixel_x + (intercept->yintercept - \
		mlx->player->pixel_y) / tan(ray->ray_angle);
	info->next_horz_touch_x = intercept->xintercept;
	info->next_horz_touch_y = intercept->yintercept;
}

// iterates through horizontal intersections. If a wall is found, it calculates
// the distance from the player to the intersection point. If no wall is found,
// it returns infinity to indicate no collision.
double	cub_check_horz_walls_update_coords(t_mlx *mlx, t_ray *ray, \
	t_ray_info *info)
{
	int		adjusted_y;
	double	horz_hit_y;

	while (info->next_horz_touch_x >= 0 && info->next_horz_touch_x < \
		mlx->map->width * BLOCK_SIZE \
		&& info->next_horz_touch_y >= 0 && info->next_horz_touch_y \
		< mlx->map->height * BLOCK_SIZE)
	{
		if (ray->is_ray_facing_down)
			adjusted_y = info->next_horz_touch_y;
		else
			adjusted_y = info->next_horz_touch_y - 1;
		if (cub_is_wall(mlx, info->next_horz_touch_x, adjusted_y))
		{
			ray->horz_hit_x = info->next_horz_touch_x;
			horz_hit_y = info->next_horz_touch_y;
			return (cub_calc_distance_between_points(mlx->player->pixel_x, \
				mlx->player->pixel_y, ray->horz_hit_x, horz_hit_y));
		}
		info->next_horz_touch_x += info->xstep;
		info->next_horz_touch_y += info->ystep;
	}
	return (INFINITY);
}

// calculates the distance to the nearest horizontal wall collision.
double	cub_calculate_horizontal_collision(t_mlx *mlx, t_ray *ray)
{
	t_ray_info	info;
	t_intercept	intercept;

	cub_init_horz_ray_info(ray, &info);
	cub_init_horz_intercepts(mlx, ray, &intercept, &info);
	return (cub_check_horz_walls_update_coords(mlx, ray, &info));
}
