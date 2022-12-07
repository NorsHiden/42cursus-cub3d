/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:10:41 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:16:25 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	frame_color(t_cub *cub, int x, int y)
{
	char	*frame_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	frame_addr = mlx_get_data_addr(
			cub->texture.frame, &bits_per_pixel, &size_line, &endian);
	return (*(int *)(frame_addr + (y * size_line + x * (bits_per_pixel / 8))));
}

void	render_frame(t_cub *cub)
{
	t_cord	pos;
	int		color;

	pos.y = 0;
	while (pos.y < cub->texture.height)
	{
		pos.x = 0;
		while (pos.x < cub->texture.width)
		{
			color = frame_color(cub, pos.x, pos.y);
			if (color != 0xFF000000)
				draw_pixel_frame(cub, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

void	display_minimap(t_cub *cub)
{
	draw_minimap(cub);
	draw_rays(cub);
	draw_player(cub);
	render_frame(cub);
	render_layer(cub);
}

void	display_3dmap(t_cub	*cub)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		cub->pos_x = i;
		render_ray(cub, &cub->rays[i]);
		i++;
	}
}

int	quit_cub3d(t_cub *cub)
{
	(void)cub;
	exit(0);
}
