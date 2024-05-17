/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 11:53:06 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/17 10:28:48 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	cub_is_wall_hit(t_mlx *mlx, int map_grid_y, int map_grid_x)
{
	if (mlx->map->field[map_grid_y][map_grid_x] != '1')
		return (1);
	return (0);
}

// calculates the new player position in pixels.
// calculates the new player position in grid cells.
// updates player position if not hitting a wall.
void	cub_move_player(t_mlx *mlx, double move_x, double move_y)
{
	int	new_map_grid_y;
	int	new_map_grid_x;
	int	new_player_pixel_x;
	int	new_player_pixel_y;

	new_player_pixel_x = roundf(mlx->player->pixel_x + move_x);
	new_player_pixel_y = roundf(mlx->player->pixel_y + move_y);
	new_map_grid_x = (new_player_pixel_x / BLOCK_SIZE);
	new_map_grid_y = (new_player_pixel_y / BLOCK_SIZE);
	if (cub_is_wall_hit(mlx, new_map_grid_y, new_map_grid_x)
		&& cub_is_wall_hit(mlx, new_map_grid_y, mlx->player->pixel_x
			/ BLOCK_SIZE)
		&& cub_is_wall_hit(mlx, mlx->player->pixel_y
			/ BLOCK_SIZE, new_map_grid_x))
	{
		mlx->player->pixel_x = new_player_pixel_x;
		mlx->player->pixel_y = new_player_pixel_y;
	}
}

void	cub_rotate_player(t_mlx *mlx)
{
	if (mlx->key->key_l_r == 'r')
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	if (mlx->key->key_l_r == 'l')
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

// calculates the movement amounts based on the players angle and speed.
void	cub_player_update_frame(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->key->key_w_s == 'w')
	{
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->key->key_w_s == 's')
	{
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->key->key_a_d == 'a')
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->key->key_a_d == 'd')
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	cub_rotate_player(mlx);
	cub_move_player(mlx, move_x, move_y);
}
