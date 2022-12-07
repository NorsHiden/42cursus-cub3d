/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:05:59 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:16:52 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line_frame(t_cub *cub, t_cord start, t_cord end, int color)
{
	t_fcord	middle;
	t_fcord	d_middle;
	double	distance;

	middle.x = 0;
	middle.y = 0;
	distance = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	d_middle.x = (end.x - start.x) / distance;
	d_middle.y = (end.y - start.y) / distance;
	while (distance-- > 0)
	{
		draw_pixel_frame(cub, start.x + middle.x, start.y + middle.y, color);
		middle.x += d_middle.x;
		middle.y += d_middle.y;
	}
}

int	get_color_from_texture(void *texture, int x, int y, double wall_height)
{
	char	*texture_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	texture_addr = mlx_get_data_addr(texture,
			&bits_per_pixel, &size_line, &endian);
	return (*(int *)(texture_addr
		+ ((int)(y * (TILE_SIZE / wall_height)) *size_line
		+ (x % TILE_SIZE) * (bits_per_pixel / 8))));
}

void	draw_texture_line(t_cub *cub, t_ray	*ray,
	double wall_height, void *texture)
{
	int	color;
	int	y;
	int	end;

	y = 0;
	if (wall_height > WINDOW_HEIGHT)
	{
		y = wall_height / 2 - WINDOW_HEIGHT / 2;
		end = wall_height / 2 + WINDOW_HEIGHT / 2;
	}
	else
		end = wall_height;
	while (y < end)
	{
		if (ray->is_hor)
			color = get_color_from_texture(texture, ray->x, y, wall_height);
		else
			color = get_color_from_texture(texture, ray->y, y, wall_height);
		draw_pixel_frame(cub, cub->pos_x,
			(WINDOW_HEIGHT / 2 - wall_height / 2 + y), color);
		y++;
	}
}
