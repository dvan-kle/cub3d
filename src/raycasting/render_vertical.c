/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_vertical.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 00:24:00 by trstn4        #+#    #+#                 */
/*   Updated: 2024/04/25 00:24:07 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

typedef struct s_vert_ray_info
{
	double	xstep_vert;
	double	ystep_vert;
	double	next_vert_touch_x;
	double	next_vert_touch_y;
}	t_vert_ray_info;

typedef struct s_vert_intercept
{
	double	xintercept_vert;
	double	yintercept_vert;
}	t_vert_intercept;

void	cub_init_vert_ray_info(t_mlx *mlx, t_ray *ray, t_vert_ray_info *info)
{
	info->xstep_vert = mlx->map->pixel_width_per_square;
	if (!ray->is_ray_facing_right)
		info->xstep_vert *= -1;
	info->ystep_vert = mlx->map->pixel_width_per_square * tan(ray->ray_angle);
	if (ray->is_ray_facing_down && info->ystep_vert < 0)
		info->ystep_vert *= -1;
	else if (!ray->is_ray_facing_down && info->ystep_vert > 0)
		info->ystep_vert *= -1;
}

void	cub_init_vert_intercepts(t_mlx *mlx, t_ray *ray, \
	t_vert_intercept *intercept, t_vert_ray_info *info)
{
	intercept->xintercept_vert = floor(mlx->player->pixel_x \
		/ mlx->map->pixel_width_per_square) * mlx->map->pixel_width_per_square;
	if (ray->is_ray_facing_right)
		intercept->xintercept_vert += mlx->map->pixel_width_per_square;
	intercept->yintercept_vert = mlx->player->pixel_y \
		+ (intercept->xintercept_vert - mlx->player->pixel_x) \
		* tan(ray->ray_angle);
	info->next_vert_touch_x = intercept->xintercept_vert;
	info->next_vert_touch_y = intercept->yintercept_vert;
}

double	cub_check_vert_walls_update_coords(t_mlx *mlx, t_ray *ray, \
	t_vert_ray_info *info)
{
	int		adjusted_x;
	double	vert_hit_x;

	while (info->next_vert_touch_x >= 0 && info->next_vert_touch_x \
		< mlx->map->width * mlx->map->pixel_width_per_square \
		&& info->next_vert_touch_y >= 0 && info->next_vert_touch_y \
		< mlx->map->height * mlx->map->pixel_height_per_square)
	{
		if (ray->is_ray_facing_right)
			adjusted_x = info->next_vert_touch_x;
		else
			adjusted_x = info->next_vert_touch_x - 1;
		if (cub_is_wall(mlx, adjusted_x, info->next_vert_touch_y))
		{
			vert_hit_x = info->next_vert_touch_x;
			ray->vert_hit_y = info->next_vert_touch_y;
			return (cub_calc_distance_between_points(mlx->player->pixel_x, \
				mlx->player->pixel_y, vert_hit_x, ray->vert_hit_y));
		}
		info->next_vert_touch_x += info->xstep_vert;
		info->next_vert_touch_y += info->ystep_vert;
	}
	return (INFINITY);
}

double	cub_calculate_vertical_collision(t_mlx *mlx, t_ray *ray)
{
	t_vert_ray_info		info;
	t_vert_intercept	intercept;

	cub_init_vert_ray_info(mlx, ray, &info);
	cub_init_vert_intercepts(mlx, ray, &intercept, &info);
	return (cub_check_vert_walls_update_coords(mlx, ray, &info));
}
