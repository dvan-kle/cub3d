/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 00:25:21 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 15:59:38 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// selects the appropriate wall texture based on ray direction and hit distance.
// handles if hit was on a horizontal or vertical wall and the facing direction.
mlx_texture_t	*cub_select_texture(t_mlx *mlx, t_ray *ray, \
	double horz_hit_distance, double vert_hit_distance)
{
	if (horz_hit_distance < vert_hit_distance)
	{
		if (ray->is_ray_facing_down)
			return (mlx->map->south_texture);
		else
			return (mlx->map->north_texture);
	}
	else
	{
		if (ray->is_ray_facing_right)
			return (mlx->map->east_texture);
		else
			return (mlx->map->west_texture);
	}
}

// Converts a color from ABGR format to RGBA format.
// Rearranges the bytes to move:
// - Alpha to the most significant byte
// - Blue to the second most significant byte
// - Green to the third most significant byte
// - Red to the least significant byte
int	cub_color_to_rgba(int color)
{
	return (((color & 0xFF) << 24)
		| ((color & 0xFF00) << 8)
		| ((color & 0xFF0000) >> 8)
		| ((color & 0xFF000000) >> 24));
}

// 1. locates where on the texture the ray hits.
// 2. stretches or compresses the parsed wall (just math) texture to fit the
//    wall slice.
// 3. copies the texture pixels to the screen/image to render the wall slice.
void	cub_draw_wall(t_mlx *mlx, t_ray *ray)
{
	int		texture_x;
	double	texture_step;
	double	texture_pos;
	int		y;
	int		tex_y;

	texture_x = (int)(fmod(ray->wall_hit_pos, BLOCK_SIZE) / BLOCK_SIZE * \
		ray->texture->width);
	texture_step = ray->texture->height / ray->wall_slice_height;
	texture_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + \
		ray->wall_slice_height / 2) * texture_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)texture_pos % ray->texture->height;
		cub_pixel_put(mlx, ray->ray_num, y, \
			cub_color_to_rgba(((uint32_t *)ray->texture->pixels)[tex_y \
			* ray->texture->width + texture_x]));
		texture_pos += texture_step;
		y++;
	}
}

// draws the wall on the image/screen at the calculated position and height.
// fills the ceiling color on every pixel above the wall and draws the floor
// color on the pixels under the wall.
void	cub_draw_ray(t_mlx *mlx, t_ray *ray)
{
	int	y;

	cub_draw_wall(mlx, ray);
	y = 0;
	while (y < ray->draw_start)
	{
		cub_pixel_put(mlx, ray->ray_num, y, mlx->map->color_ceiling);
		y++;
	}
	y = ray->draw_end;
	while (y < SCREEN_HEIGHT)
	{
		cub_pixel_put(mlx, ray->ray_num, y, mlx->map->color_floor);
		y++;
	}
}
