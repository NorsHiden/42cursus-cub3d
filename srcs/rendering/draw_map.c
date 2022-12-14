/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:40:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:17:16 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_pixel_frame(t_cub *cub, int x, int y, int color)
{
	char	*pos;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	pos = cub->settings.frame_addr
		+ (y * cub->settings.frame_size_line
			+ (x * (cub->settings.frame_bits_per_pixel / 8)));
	*(int *)pos = color;
}

void	draw_pixel(t_cub *cub, int x, int y, int color)
{
	char	*pos;

	if (x < 0 || x >= cub->map_width * TILE_SIZE
		|| y < 0 || y >= cub->map_height * TILE_SIZE)
		return ;
	pos = cub->settings.minimap_layer_addr
		+ (y * cub->settings.minimap_size_line
			+ (x * (cub->settings.minimap_bits_per_pixel / 8)));
	*(int *)pos = color;
}

void	draw_line(t_cub *cub, t_cord start, t_cord end, int color)
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
		draw_pixel(cub, start.x + middle.x, start.y + middle.y, color);
		middle.x += d_middle.x;
		middle.y += d_middle.y;
	}
}

void	draw_square(t_cub *cub, t_cord pos, int color)
{
	t_cord	f;

	f.y = 0;
	while (f.y < MAP_TILE_SIZE)
	{
		draw_pixel(cub, ((pos.x * MAP_TILE_SIZE) + 0),
			((pos.y * MAP_TILE_SIZE) + f.y), 0);
		f.x = 0;
		while (f.x < MAP_TILE_SIZE)
		{
			draw_pixel(cub, ((pos.x * MAP_TILE_SIZE) + f.x),
				((pos.y * MAP_TILE_SIZE) + f.y), color);
			f.x++;
		}
		f.y++;
	}
}

void	draw_minimap(t_cub *cub)
{
	t_cord	pos;
	t_cord	end;

	if ((int)(cub->player.y / TILE_SIZE) < 5)
		pos.y = 0;
	else
		pos.y = (int)(cub->player.y / TILE_SIZE) - 5;
	while (cub->map[pos.y] && pos.y < (int)(cub->player.y / TILE_SIZE) + 10)
	{
		if ((int)(cub->player.x / TILE_SIZE) < 5)
			pos.x = 0;
		else
			pos.x = (int)(cub->player.x / TILE_SIZE) - 5;
		while (cub->map[pos.y][pos.x]
			&& pos.x < (int)(cub->player.x / TILE_SIZE) + 10)
		{
			if (cub->map[pos.y][pos.x] == '1')
				draw_square(cub, pos, 0xA67C58);
			else if (ft_strchr("0NSWE", cub->map[pos.y][pos.x]))
				draw_square(cub, pos, 0xD9BBA0);
			pos.x++;
		}
		pos.y++;
	}
}
