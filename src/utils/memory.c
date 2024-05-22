/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 13:52:17 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/22 13:26:04 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	*allocate_memory(size_t buffer_size)
{
	void	*buffer;

	buffer = (void *)malloc(buffer_size);
	if (!buffer)
		cub_error(1, "Error\nMalloc failed to allocate memory.\n");
	return (buffer);
}
