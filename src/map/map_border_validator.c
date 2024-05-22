/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_border_validator.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 11:53:14 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 13:23:14 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	cub_is_out_of_bounds(t_check_map *check_map, int check_x, int check_y)
{
	if (check_x < 0 || check_y < 0 || check_x >= check_map->height
		|| check_y >= check_map->width)
		return (1);
	else
		return (0);
}

int	cub_check_surroundings(t_check_map *check_map, int x, int y)
{
	int		i;
	int		j;
	char	adjacent;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if ((i == 0 || j == 0) && !(i == 0 && j == 0))
			{
				if (!cub_is_out_of_bounds(check_map, x + i, y + j))
				{
					adjacent = check_map->field[x + i][y + j];
					if (adjacent != '1' && adjacent != '.' && adjacent != '\n' \
						&& adjacent != '\0')
						return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	cub_is_border_valid(t_check_map *check_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < check_map->height)
	{
		j = 0;
		while (j < check_map->width)
		{
			if (check_map->field[i][j] == '.')
			{
				if (cub_check_surroundings(check_map, i, j) == 1)
					cub_error(1, "Error\nMap must be closed by walls.\n");
			}
			j++;
		}
		i++;
	}
}
