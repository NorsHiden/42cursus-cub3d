/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:31:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/05 18:29:33 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>

# define RED "\033[0;31m"
# define RESET "\033[0;37m"

# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F_C 5
# define C_C 6

# define WINDOW_WIDTH 1366
# define WINDOW_HEIGHT 768

# define MINIMAP_FACTOR 1
# define TILE_SIZE 32

# define MAP_TILE_SIZE TILE_SIZE / MINIMAP_FACTOR
# define PLAYER_SIZE MAP_TILE_SIZE / 4

# define MAP_TILE_FACTOR (double)WINDOW_WIDTH / (double)MINIMAP_FACTOR

# define LARGE_TO_SMALL_SCALE (MAP_TILE_FACTOR / (double)WINDOW_WIDTH)

# define PI 3.14159265359
# define PPM 10
# define FOV_DEGREE 60

# define UP 13
# define RIGHT 2
# define DOWN 1
# define LEFT 0
# define LEFT_ARR 123
# define RIGHT_ARR 124

typedef struct s_file_data
{
	int		fd;
	char	*no_filename;
	char	*so_filename;
	char	*we_filename;
	char	*ea_filename;
	char	*floor_color;
	char	*ceiling_color;
	char	**file_data;
	size_t	map_idx;
}	t_file_data;

typedef struct s_texture
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_settings
{
	void		*mlx;
	void		*window;
	void		*minimap_layer;
	char		*minimap_layer_addr;
	int			minimap_bits_per_pixel;
	int			minimap_size_line;
	int			minimap_endian;
	void		*frame;
	char		*frame_addr;
	int			frame_bits_per_pixel;
	int			frame_size_line;
	int			frame_endian;
}	t_settings;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle_rotation;
}	t_player;

typedef struct s_cord
{
	int	x;
	int	y;
}	t_cord;

typedef struct s_fcord
{
	double	x;
	double	y;
}	t_fcord;

typedef struct s_ray
{
	double	x;
	double	y;
	double	angle_rotation;
	int		is_facing_up;
	int		is_facing_left;
	double	distance;
	int		is_hor;
}	t_ray;

typedef struct s_cub
{
	t_file_data	data;
	t_texture	texture;
	t_settings	settings;
	t_player	player;
	t_cord		start;
	t_ray		rays[WINDOW_WIDTH];
	char		**map;
	int			map_height;
	int			map_width;
	int			player_orientation;
	int			pos_x;
}	t_cub;

/*------------------IMPORT_FUNCTIONS---------------------------*/
void	import_cardinal_direction(t_cub *cub, size_t *idx, int sym);
void	import_data(t_cub *cub);
void	import_color(t_cub *cub, size_t *idx, int sym);
void	fill_map(t_cub *cub);
void	import_map(t_cub *cub);
void	import_configs(t_cub *cub);
void	import_file(t_cub *cub, char *filename);
void	import_symbol(t_cub *cub, int symbol, char *line);
char	**pointer_to_target_symbol(t_cub *cub, int symbol);
int		find_symbol(char *line);
int		is_rgb(char *line, size_t i);
int		is_cardinal_directions(char *line, size_t i);

/*--------------MAP_AND_TEXTURE_VALIDATION_FUNCTIONS-----------------*/
void	import_texture(t_cub *cub);
void	*valid_texture(t_cub *cub, char *filename);
int		valid_color(t_cub *cub, char *color, char c);
int		grab_color(char *color, size_t *i);
void	check_color(char *color, int *full_color, int *times);
void	adjust_map_size(t_cub *cub);
void	map_valid(t_cub *cub);
void	check_line_validation(char **map, int *player_orientation, size_t y);
void	check_symbol_sensitivity(char **map, size_t y, size_t x, char sym);
size_t	ptrlen(char **str);

/*--------------------MINIMAP_FUNCTIONS--------------------------*/
void	draw_player(t_cub *cub);
void	setup_player(t_cub *cub);
void	fill_player(t_cub *cub, t_cord pos);
void	draw_pixel(t_cub *cub, int x, int y, int color);
void	draw_pixel_frame(t_cub *cub, int x, int y, int color);
void	draw_minimap(t_cub *cub);
void	draw_square(t_cub *cub, t_cord pos, t_cord *start, int color);
void	draw_line(t_cub *cub, t_cord start, t_cord end, int color);
void	display_minimap(t_cub *cub);
void	update_rays(t_cub *cub);
void	cast_ray(t_cub *cub, double angle, int idx);
t_fcord	get_vertical_intersection(t_cub *cub, t_ray *ray);
t_fcord	get_horizontal_intersection(t_cub *cub, t_ray *ray);
void	render_layer(t_cub *cub);
int		get_color_from_minimap(t_cub *cub, int x, int y);
void	draw_rays(t_cub *cub);
void	display_minimap(t_cub *cub);

/*--------------------GAME_FUNCTIONS--------------------------*/
void	launch_game(t_cub *cub);

/*--------------------3D_MAP_FUNCTIONS--------------------------*/
void	display_3dmap(t_cub	*cub);

/*--------------------HOOK_FUNCTIONS--------------------------*/
int		key_pressed(int key, t_cub *cub);

/*-----------------ERROR_HANDLING_FUNCTIONS--------------------*/
void	throw_error(char *err, char *cause);

#endif /* CUB3D_H */