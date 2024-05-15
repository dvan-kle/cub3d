/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 23:27:32 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/15 16:41:23 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cub_exit(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->map->field[i])
		free(mlx->map->field[i++]);
	free(mlx->map->field);
	free(mlx->map);
	free(mlx->player);
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	mlx_terminate(mlx->mlx_p);
	printf("Exited cub3D cleanly.\n");
	exit(0);
}
