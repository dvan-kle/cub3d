/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 17:16:59 by trstn4        #+#    #+#                 */
/*   Updated: 2024/03/18 17:10:55 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cub_check_key_release(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->key->key_w_s = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->key->key_w_s = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->key->key_a_d = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->key->key_a_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->key->key_l_r = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->key->key_l_r = 0;
}

void	cub_check_key(mlx_key_data_t keydata, void *parsed_mlx)
{
	t_mlx	*mlx;

	mlx = parsed_mlx;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->key->key_w_s = 'w';
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		mlx->key->key_w_s = 's';
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		mlx->key->key_a_d = 'a';
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		mlx->key->key_a_d = 'd';
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->key->key_l_r = 'l';
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->key->key_l_r = 'r';
	else if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		cub_exit(mlx);
	cub_check_key_release(keydata, mlx);
}
