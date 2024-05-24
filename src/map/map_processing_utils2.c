/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_processing_utils2.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:52:36 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/24 11:01:45 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	cub_check_empty_line(char *new_line)
{
	int	i;
	int	is_empty;

	i = 0;
	is_empty = 1;
	while (ft_isspace(new_line[i]) != 1)
	{
		if (new_line[i] == '\0')
		{
			is_empty = 0;
			break ;
		}
		i++;
	}
	return (is_empty);
}

char	*cub_extract_value(char *line)
{
	char	*value_start;

	value_start = ft_strchr(line, ' ');
	if (!value_start)
		return (ft_strdup(""));
	return (cub_trim_whitespace(value_start + 1));
}

void	cub_assign_and_check(char *new_line, char **id)
{
	if (*id)
	{
		free(new_line);
		cub_error(1, "Error\nDuplicate identifier.\n");
	}
	*id = cub_extract_value(new_line);
}
