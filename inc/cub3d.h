/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/06 11:52:59 by trstn4        #+#    #+#                 */
/*   Updated: 2024/05/24 11:53:42 by dvan-kle      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 64

# define FOV 65
# define ROTATION_SPEED 0.052
# define PLAYER_SPEED 4

typedef struct s_ray
{
	double			ray_angle;
	double			angle_increment;
	double			distance_to_proj_plane;
	int				ray_num;
	int				is_ray_facing_down;
	int				is_ray_facing_right;
	int				draw_start;
	int				draw_end;
	mlx_texture_t	*texture;
	double			wall_hit_pos;
	double			wall_slice_height;
	double			perp_distance;
	double			horz_hit_x;
	double			vert_hit_y;
	double			horz_hit_distance;
	double			vert_hit_distance;
}	t_ray;

typedef struct s_player
{
	int		pixel_x;
	int		pixel_y;
	char	direction;
	double	angle;
	double	fov_rd;
}	t_player;

typedef struct s_key
{
	int		key_w_s;
	int		key_a_d;
	int		key_l_r;
}	t_key;

typedef struct s_map
{
	char			**field;
	int				player_start_x;
	int				player_start_y;
	int				width;
	int				height;
	int				*row_lengths;
	char			*id_no;
	char			*id_so;
	char			*id_ea;
	char			*id_we;
	char			*id_f;
	char			*id_c;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	int				color_floor;
	int				color_ceiling;
}	t_map;

typedef struct s_check_map
{
	char	**field;
	int		width;
	int		height;
}	t_check_map;

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*mlx_p;
	t_map		*map;
	t_check_map	*check_map;
	t_player	*player;
	t_key		*key;
	t_ray		*ray;
}	t_mlx;

typedef struct s_ray_info
{
	double	ystep;
	double	xstep;
	double	next_horz_touch_x;
	double	next_horz_touch_y;
}	t_ray_info;

typedef struct s_intercept
{
	double	yintercept;
	double	xintercept;
}	t_intercept;

typedef struct s_vert_ray_info
{
	double	xstep_vert;
	double	ystep_vert;
	double	next_vert_touch_x;
	double	next_vert_touch_y;
}	t_vert_ray_info;

typedef struct s_vert_intercept
{
	double	xintercept_vert;
	double	yintercept_vert;
}	t_vert_intercept;

typedef struct s_player_start_info
{
	int		count;
	int		x;
	int		y;
	char	direction;
}	t_player_start_info;

// Map:
void			cub_is_cub_extension(char *file);
int				cub_validate_map(t_map *map);
void			cub_check_map_characters(t_map *map);
int				cub_setup_map_checks(t_map *map, t_check_map *check_map);
void			cub_is_border_valid(t_check_map *check_map);
t_map			*cub_load_map_values(char *file);
void			cub_check_and_set_player(t_mlx *mlx);
void			cub_set_player_start_position(t_mlx *mlx);
void			cub_finalize_map(t_map *map);
t_map			*cub_init_map_and_open_file(char *file, int *fd, int *fd2);
void			cub_allocate_map_field(t_map *map);
char			*cub_trim_whitespace(char *str);
char			*cub_trim_first_whitespace(char *str);
void			cub_process_lines(int fd, t_map *map, int *start_map);
void			cub_fill_map(int fd, t_map *map, int start_map);
unsigned int	cub_parse_rgb_string_to_hex(char *rgb_string);
int				cub_check_empty_line(char *new_line);
void			cub_map_save_row_lengths(t_map *map);
void			cub_assign_and_check(char *new_line, char **id);

// Movement:
void			cub_check_key(mlx_key_data_t keydata, void *parsed_mlx);
void			cub_player_update_frame(t_mlx *mlx, double move_x,
					double move_y);

// Render:
void			cub_cast_rays(t_mlx *mlx);
void			cub_pixel_put(t_mlx *mlx, int x, int y, int color);
int				cub_is_wall(t_mlx *mlx, int x, int y);
double			cub_calc_distance_between_points(double x1, double y1, \
					double x2, double y2);
int				cub_max(int a, int b);
float			cub_min(float a, float b);
mlx_texture_t	*cub_select_texture(t_mlx *mlx, t_ray *ray, \
					double horz_hit_distance, double vert_hit_distance);
double			cub_calculate_horizontal_collision(t_mlx *mlx, t_ray *ray);
double			cub_calculate_vertical_collision(t_mlx *mlx, t_ray *ray);
void			cub_draw_ray(t_mlx *mlx, t_ray *ray);
void			cub_calculate_wall_position_and_height(t_mlx *mlx, t_ray *ray);

// Utils:
void			*allocate_memory(size_t buffer_size);
void			*memory_realloc(void *ptr, size_t new_size);
void			free_memory(void *buffer);
void			cub_error(int exit_code, char *message);
void			cub_exit(t_mlx *mlx);

#endif
