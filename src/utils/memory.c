/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 13:52:17 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/15 18:33:35 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	*allocate_memory(size_t buffer_size)
{
	void	*buffer;

	buffer = (void *)malloc(buffer_size);
	if (!buffer)
		cub_error(-1, "Error: Malloc failed to allocate memory.");
	return (buffer);
}

void	free_memory(void *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

void	*memory_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free_memory(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (allocate_memory(new_size));
	new_ptr = allocate_memory(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free_memory(ptr);
	return (new_ptr);
}
