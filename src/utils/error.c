/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 13:53:04 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/15 18:33:11 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	cub_error(int exit_code, char *message)
{
	printf("%s", message);
	exit(exit_code);
}
