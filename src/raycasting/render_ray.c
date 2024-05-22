/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_ray.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 17:30:23 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 16:46:42 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// - facing down when the ray is moving towards the bottom of the map
//      (positive y-direction).
// - facing up when the ray is moving towards the top of the map
//      (negative y-direction).
// - facing rightwhen the ray is moving towards the right side of the map
//      (positive x-direction).
// - facing left when the ray is moving towards the left side of the map
//      (negative x-direction).

// - horizontal walls extend horizontally across the map, 
//  	parallel to the x-axis.
// - vertical walls extend vertically across the map, parallel to the y-axis.

// casts a single ray, calculates collisions with walls, determines wall
// position and height, and draws the ray/wall.
// - ray is facing down if angle is between 0 and 180 degrees.
// - ray is facing right if angle is less than (90 degrees) or greater than
//   (270 degrees).
void	cub_cast_single_ray(t_mlx *mlx, t_ray *ray)
{
	ray->horz_hit_x = 0;
	ray->vert_hit_y = 0;
	ray->is_ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->is_ray_facing_right = ray->ray_angle < 0.5 * M_PI \
		|| ray->ray_angle > 1.5 * M_PI;
	ray->horz_hit_distance = cub_calculate_horizontal_collision(mlx, ray);
	ray->vert_hit_distance = cub_calculate_vertical_collision(mlx, ray);
	cub_calculate_wall_position_and_height(mlx, ray);
	cub_draw_ray(mlx, ray);
}

// loops through each position on the given screen size, casting rays across
// the players FOV to render the 3D illusion.
//
// - ray_angle initialises the first ray angle (leftmost ray).
// - angle_increment calculates the angle increment between each ray. The FOV
//   is divided by the screen width (number of vertical columns of pixels).
//   (coverting using (M_PI / 180.0) to radians)
// - "distance to the projection plane" helps calculate how tall an object
//   should appear based on its distance from the player
void	cub_cast_rays(t_mlx *mlx)
{
	t_ray	ray;

	ray.ray_angle = mlx->player->angle - (FOV / 2.0 * (M_PI / 180.0));
	ray.angle_increment = FOV / (double)SCREEN_WIDTH * (M_PI / 180.0);
	ray.distance_to_proj_plane = (SCREEN_WIDTH / 2.0) / tan(FOV / 2.0 * \
		(M_PI / 180.0));
	ray.ray_num = 0;
	while (ray.ray_num < SCREEN_WIDTH)
	{
		ray.ray_angle = fmod(ray.ray_angle, 2.0 * M_PI);
		if (ray.ray_angle < 0)
			ray.ray_angle += 2.0 * M_PI;
		cub_cast_single_ray(mlx, &ray);
		ray.ray_angle += ray.angle_increment;
		ray.ray_num++;
	}
}
