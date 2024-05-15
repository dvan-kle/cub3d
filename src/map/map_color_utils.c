/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_color_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:50:42 by trstn4        #+#    #+#                 */
/*   Updated: 2024/04/03 14:50:53 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	cub_rgb_to_hex(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255 << 0);
}

unsigned int	cub_parse_rgb_string_to_hex(char *rgb_string)
{
	char			**rgb_parts;
	unsigned int	hex_color;
	int				i;

	rgb_parts = ft_split(rgb_string, ',');
	if (!rgb_parts)
		return (0);
	hex_color = cub_rgb_to_hex(ft_atoi(rgb_parts[0]), ft_atoi(rgb_parts[1]),
			ft_atoi(rgb_parts[2]));
	i = 0;
	while (rgb_parts[i] != NULL)
	{
		free(rgb_parts[i]);
		i++;
	}
	free(rgb_parts);
	return (hex_color);
}
