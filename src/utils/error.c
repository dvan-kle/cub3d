/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 13:53:04 by trstn4        #+#    #+#                 */
/*   Updated: 2024/03/06 13:53:34 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cub_handle_error(int exit_code, char *message)
{
	perror(message);
	exit(exit_code);
}
