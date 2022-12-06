/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:46:28 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/05 18:20:32 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*valid_texture(t_cub *cub, char *filename)
{
	int		width;
	int		height;
	void	*texture;

	width = 0;
	height = 0;
	texture = mlx_xpm_file_to_image(cub->settings.mlx,
			filename, &width, &height);
	if (!texture)
		throw_error(": inaccessible texture", filename);
	else if (width != TILE_SIZE || height != TILE_SIZE)
		throw_error(": incompatible texture size", filename);
	return (texture);
}

int	grab_color(char *color, size_t *i)
{
	int	portion_color;

	portion_color = 0;
	while (color[*i] && ft_isdigit(color[*i]))
	{
		portion_color = (portion_color * 10) + (color[*i] - 48);
		if (portion_color > 255)
			throw_error(": no rgb color found3", color);
		(*i)++;
	}
	return (portion_color);
}

void	check_color(char *color, int *full_color, int *times)
{
	size_t	i;

	i = 0;
	while (color[i])
	{
		if (ft_isdigit(color[i]))
		{
			(*full_color) += grab_color(color, &i);
			if (*times < 2)
				*full_color = (*full_color) << 8;
			(*times)++;
			if (color[i] == ',')
				i++;
		}
		else if (color[i] != ' ')
			throw_error(": no rgb color found1", color);
		else
			i++;
	}
}

int	valid_color(t_cub *cub, char *color, char c)
{
	int		full_color;
	int		times;

	full_color = 0;
	times = 0;
	check_color(ft_strchr(color, c) + 1, &full_color, &times);
	return (full_color);
}

void	import_texture(t_cub *cub)
{
	cub->texture.no = valid_texture(cub, cub->data.no_filename);
	cub->texture.so = valid_texture(cub, cub->data.so_filename);
	cub->texture.we = valid_texture(cub, cub->data.we_filename);
	cub->texture.ea = valid_texture(cub, cub->data.ea_filename);
	cub->texture.floor = valid_color(cub, cub->data.floor_color, 'F');
	cub->texture.ceiling = valid_color(cub, cub->data.ceiling_color, 'C');
	adjust_map_size(cub);
}
