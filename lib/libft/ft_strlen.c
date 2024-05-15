/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:36:16 by tvan-bee      #+#    #+#                 */
/*   Updated: 2024/03/13 23:36:32 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strlen() function computes the length of the string s.

PARAMETERS
	s: The string which length will be counted.

RETURN VALUES
    The strlen() function returns the number of characters that precede the
	terminating NUL character.
*/

/*
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	// Increases length '+1' if index is not equal to terminator character '\0'.
	while (s[i])
		i++;
	// Returns length.
	return (i);
}
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
