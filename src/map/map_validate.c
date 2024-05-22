/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validate.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 12:03:11 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 13:26:59 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	cub_is_char_in_here(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'W' || c == 'S'
		|| c == '\n' || c == '\0');
}

void	cub_check_map_characters(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->field[i][j] != '\0')
		{
			if (map->field[i][j] != ' ' && map->field[i][j] != '\t')
			{
				if (!cub_is_char_in_here(map->field[i][j]))
				{
					printf("Error\nCharacter: '%c' is not allowed.\n",
						map->field[i][j]);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

void	cub_is_cub_extension(char *file)
{
	char	*extension;
	int		path_len;
	int		ext_len;

	extension = ".cub";
	path_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len || !ft_strnstr(file + path_len - ext_len,
			extension, path_len))
		cub_error(1, "Error\nThe file doesn't have the '.cub' extension.\n");
}

int	cub_validate_map(t_map *map)
{
	t_check_map	*check_map;
	int			i;

	i = 0;
	check_map = ft_calloc(1, sizeof(t_check_map));
	cub_setup_map_checks(map, check_map);
	cub_is_border_valid(check_map);
	while (i < check_map->height)
	{
		free(check_map->field[i]);
		i++;
	}
	free(check_map->field);
	free(check_map);
	return (0);
}
