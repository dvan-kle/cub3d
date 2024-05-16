/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_trim_lines.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dvan-kle <dvan-kle@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:43:43 by dvan-kle      #+#    #+#                 */
/*   Updated: 2024/05/16 13:53:19 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*cub_trim_first_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;

	while (ft_isspace((unsigned char)*str))
		str++;
	start = str;
	if (*str == 0)
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	result = (char *)malloc(end - start + 2);
	if (!result)
		cub_error(1, "Error: Memory allocation failed.\n");
	if (result)
	{
		ft_strncpy(result, start, end - start + 1);
		result[end - start + 1] = '\0';
	}
	return (result);
}

char	*cub_trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;

	while (ft_isspace((unsigned char)*str))
		str++;
	start = str;
	if (*str == 0)
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	result = (char *)malloc(end - start + 2);
	if (!result)
		cub_error(1, "Error: Memory allocation failed.\n");
	if (result)
	{
		ft_strncpy(result, start, end - start + 1);
		result[end - start + 1] = '\0';
	}
	return (result);
}
