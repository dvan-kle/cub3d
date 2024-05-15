/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_processing_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/03 14:52:36 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/15 15:47:38 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char    *cub_trim_first_whitespace(char *str)
{
    char    *start;
    char    *end;
    char    *result;

    while (ft_isspace((unsigned char)*str))
        str++;
    start = str;
    if (*str == 0)
        return (ft_strdup(""));
    end = str + ft_strlen(str) - 1;
    result = (char *)malloc(end - start + 2);
    if (result)
    {
        ft_strncpy(result, start, end - start + 1);
        result[end - start + 1] = '\0';
    }
    return (result);
}

char    *cub_trim_whitespace(char *str)
{
    char    *start;
    char    *end;
    char    *result;

    while (ft_isspace((unsigned char)*str))
        str++;
    start = str;
    if (*str == 0)
        return (ft_strdup(""));
    end = str + ft_strlen(str) - 1;
    while (end > str && ft_isspace((unsigned char)*end))
        end--;
    result = (char *)malloc(end - start + 2);
    if (result)
    {
        ft_strncpy(result, start, end - start + 1);
        result[end - start + 1] = '\0';
    }
    return (result);
}

char    *cub_extract_value(char *line)
{
    char    *value_start;

    value_start = ft_strchr(line, ' ');
    if (!value_start)
        return (ft_strdup(""));
    return (cub_trim_whitespace(value_start + 1));
}

void    cub_store_identifier_value(char *line, t_map *map)
{
    char *new_line;

    new_line = cub_trim_first_whitespace(line);
    if (ft_strncmp(new_line, "NO", 2) == 0)
        map->id_no = cub_extract_value(new_line);
    else if (ft_strncmp(new_line, "SO", 2) == 0)
        map->id_so = cub_extract_value(new_line);
    else if (ft_strncmp(new_line, "WE", 2) == 0)
        map->id_we = cub_extract_value(new_line);
    else if (ft_strncmp(new_line, "EA", 2) == 0)
        map->id_ea = cub_extract_value(new_line);
    else if (ft_strncmp(new_line, "F", 1) == 0)
        map->id_f = cub_extract_value(new_line);
    else if (ft_strncmp(new_line, "C", 1) == 0)
        map->id_c = cub_extract_value(new_line);
    free(new_line);
}

void    cub_process_map_line(char *line, t_map *map, int *i, int *max_width)
{
    char    **temp;
    int     line_length;

    temp = memory_realloc(map->field, (*i + 2) * sizeof(char *));
    if (!temp)
    {
        perror("Error\nMemory reallocation failed for map line");
        exit(1);
    }
    map->field = temp;
    map->field[(*i)++] = line;
    line_length = ft_strlen(line);
    if (line_length > *max_width)
        *max_width = line_length;
}

void    cub_process_lines(int fd, t_map *map)
{
    char    *line;
    int     max_width;
    int     i;

    max_width = 0;
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (map->id_no && map->id_so && map->id_we && map->id_ea && map->id_f && map->id_c)
            cub_process_map_line(line, map, &i, &max_width);
        else
        {
            cub_store_identifier_value(line, map);
            free(line);
        }
        line = get_next_line(fd);
    }
	if (!map->id_no || !map->id_so || !map->id_we || !map->id_ea || !map->id_f || !map->id_c || !map->field)
    {
        printf("Error\nMap missing one or more identifier.\n");
        exit(1);
    }
    cub_finalize_map(map, i, max_width);
}

