/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:31:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/30 08:51:17 by nelidris         ###   ########.fr       */
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

# define TILE_SIZE 32

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

typedef struct s_cub
{
	t_file_data	data;
	t_texture	texture;
	void		*mlx;
	void		*window;
	char		**map;
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
void	check_line_validation(char **map, size_t y);
void	check_symbol_sensitivity(char **map, size_t y, size_t x, char sym);
size_t	ptrlen(char **str);

/*-----------------ERROR_HANDLING_FUNCTIONS--------------------*/
void	throw_error(char *err, char *cause);

#endif /* CUB3D_H */