/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:40:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/04 13:21:31 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_pixel(t_cub *cub, int x, int y, int color)
{
	char	*pos;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	pos = cub->settings.frame_addr
		+ (y * cub->settings.size_line
			+ (x * (cub->settings.bits_per_pixel / 8)));
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

void	draw_square(t_cub *cub, t_cord pos, t_cord *start, int color)
{
	t_cord	f;

	f.y = 0;
	while (f.y < MAP_TILE_SIZE)
	{
		f.x = 1;
		while (f.x < MAP_TILE_SIZE)
		{
			if (f.y % MAP_TILE_SIZE)
				draw_pixel(cub, ((pos.x * MAP_TILE_SIZE) + start->x + f.x),
					((pos.y * MAP_TILE_SIZE) + start->y + f.y), color);
			f.x++;
		}
		f.y++;
	}
}

void	draw_minimap(t_cub *cub)
{
	t_cord	pos;

	pos.y = 0;
	while (cub->map[pos.y])
	{
		pos.x = 0;
		while (cub->map[pos.y][pos.x])
		{
			if (cub->map[pos.y][pos.x] == '1')
				draw_square(cub, pos, &cub->start, 0xFFFFFF);
			else if (ft_strchr("0NSWE", cub->map[pos.y][pos.x]))
				draw_square(cub, pos, &cub->start, 0xAAAAAA);
			pos.x++;
		}
		pos.y++;
	}
}
