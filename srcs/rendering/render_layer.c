/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_layer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 15:11:49 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:22:55 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_rays(t_cub *cub)
{
	t_cord	start;
	t_cord	end;
	int		i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		start.x = cub->player.x * LARGE_TO_SMALL_SCALE;
		start.y = cub->player.y * LARGE_TO_SMALL_SCALE;
		if (cub->rays[i].distance > 160)
		{
			end.x = (cub->player.x + cos(cub->rays[i].angle_rotation) * 160)
				* LARGE_TO_SMALL_SCALE;
			end.y = (cub->player.y + sin(cub->rays[i].angle_rotation) * 160)
				* LARGE_TO_SMALL_SCALE;
		}
		else
		{
			end.x = cub->rays[i].x * LARGE_TO_SMALL_SCALE;
			end.y = cub->rays[i].y * LARGE_TO_SMALL_SCALE;
		}
		draw_line(cub, start, end, 0xF2E4DC);
		i++;
	}
}

int	get_color_from_minimap(t_cub *cub, int x, int y)
{
	if (x < 0 || x >= cub->map_width * TILE_SIZE
		|| y < 0 || y >= cub->map_height * TILE_SIZE)
		return (-1);
	return (*(int *)(cub->settings.minimap_layer_addr
		+ (y * cub->settings.minimap_size_line
			+ (x * (cub->settings.minimap_bits_per_pixel / 8)))));
}

void	render_layer(t_cub *cub)
{
	t_cord	start;
	t_cord	pos;
	int		color;

	start.x = cub->player.x - 100;
	start.y = cub->player.y - 100;
	pos.y = 0;
	while (pos.y < 200)
	{
		pos.x = 0;
		while (pos.x < 200)
		{
			color = get_color_from_minimap(cub,
					start.x + pos.x, start.y + pos.y);
			if (color <= 0)
				color = 0x2b1b12;
			draw_pixel_frame(cub,
				cub->start.x + pos.x,
				cub->start.y + pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}
