/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_player.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 10:38:05 by trstn4        #+#    #+#                 */
/*   Updated: 2024/04/04 14:38:28 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

typedef struct s_player_start_info
{
	int		count;
	int		x;
	int		y;
	char	direction;
}	t_player_start_info;

void	cub_decide_if_player_error(int count)
{
	if (count == 0)
	{
		printf("Error\nMissing player start position.\n");
		exit(1);
	}
	else if (count > 1)
	{
		printf("Error\nMultiple player start positions detected.\n");
		exit(1);
	}
	else
		return ;
}

void	cub_set_player_location(t_mlx *mlx, t_player_start_info *info)
{
	info->count += 1;
	mlx->map->player_start_y = info->y;
	mlx->map->player_start_x = info->x;
	mlx->player->direction = info->direction;
	mlx->player->fov_rd = (FOV * M_PI) / 180;
}

void	cub_check_and_set_player(t_mlx *mlx)
{
	t_player_start_info	info;

	info.count = 0;
	info.y = 0;
	while (info.y < mlx->map->height)
	{
		info.x = 0;
		while (mlx->map->field[info.y][info.x] != '\0')
		{
			if (mlx->map->field[info.y][info.x] == 'N'
				|| mlx->map->field[info.y][info.x] == 'E'
				|| mlx->map->field[info.y][info.x] == 'S'
				|| mlx->map->field[info.y][info.x] == 'W')
			{
				info.direction = mlx->map->field[info.y][info.x];
				cub_set_player_location(mlx, &info);
			}
			info.x++;
		}
		info.y++;
	}
	cub_decide_if_player_error(info.count);
}
