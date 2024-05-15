/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_horizontal.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 00:24:32 by trstn4        #+#    #+#                 */
/*   Updated: 2024/04/25 00:24:39 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

typedef struct s_ray_info
{
	double	ystep;
	double	xstep;
	double	next_horz_touch_x;
	double	next_horz_touch_y;
}	t_ray_info;

typedef struct s_intercept
{
	double	yintercept;
	double	xintercept;
}	t_intercept;

void	cub_init_horz_ray_info(t_mlx *mlx, t_ray *ray, t_ray_info *info)
{
	info->ystep = mlx->map->pixel_height_per_square;
	info->xstep = mlx->map->pixel_height_per_square / tan(ray->ray_angle);
	if (ray->is_ray_facing_down)
		info->ystep *= 1;
	else
		info->ystep *= -1;
	if (ray->is_ray_facing_right && info->xstep < 0)
		info->xstep *= -1;
	else if (!ray->is_ray_facing_right && info->xstep > 0)
		info->xstep *= -1;
}

void	cub_init_horz_intercepts(t_mlx *mlx, t_ray *ray, \
	t_intercept *intercept, t_ray_info *info)
{
	intercept->yintercept = floor(mlx->player->pixel_y / \
		mlx->map->pixel_height_per_square) * mlx->map->pixel_height_per_square;
	if (ray->is_ray_facing_down)
		intercept->yintercept += mlx->map->pixel_height_per_square;
	intercept->xintercept = mlx->player->pixel_x + (intercept->yintercept - \
		mlx->player->pixel_y) / tan(ray->ray_angle);
	info->next_horz_touch_x = intercept->xintercept;
	info->next_horz_touch_y = intercept->yintercept;
}

double	cub_check_horz_walls_update_coords(t_mlx *mlx, t_ray *ray, \
	t_ray_info *info)
{
	int		adjusted_y;
	double	horz_hit_y;

	while (info->next_horz_touch_x >= 0 && info->next_horz_touch_x < \
		mlx->map->width * mlx->map->pixel_width_per_square \
		&& info->next_horz_touch_y >= 0 && info->next_horz_touch_y \
		< mlx->map->height * mlx->map->pixel_height_per_square)
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

double	cub_calculate_horizontal_collision(t_mlx *mlx, t_ray *ray)
{
	t_ray_info	info;
	t_intercept	intercept;

	cub_init_horz_ray_info(mlx, ray, &info);
	cub_init_horz_intercepts(mlx, ray, &intercept, &info);
	return (cub_check_horz_walls_update_coords(mlx, ray, &info));
}
