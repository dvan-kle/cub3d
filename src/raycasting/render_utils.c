/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/25 00:22:58 by trstn4        #+#    #+#                 */
/*   Updated: 2024/04/25 00:28:01 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	cub_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float	cub_min(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	cub_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		mlx_put_pixel(mlx->img, x, y, color);
}
