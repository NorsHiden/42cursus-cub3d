/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:05:06 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:18:13 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	render_ceiling(t_cub *cub, int x, double wall_height)
{
	int	y;
	int	end;

	y = 0;
	end = (WINDOW_HEIGHT / 2) - wall_height / 2;
	while (y < end)
	{
		draw_pixel_frame(cub, x, y, cub->texture.ceiling);
		y++;
	}
}

void	render_floor(t_cub *cub, int x, double wall_height)
{
	int	y;
	int	end;

	y = WINDOW_HEIGHT / 2 + wall_height / 2;
	end = WINDOW_HEIGHT;
	while (y < end)
	{
		draw_pixel_frame(cub, x, y, cub->texture.floor);
		y++;
	}
}

void	render_ray(t_cub *cub, t_ray *ray)
{
	double	wall_height;

	wall_height = (
			TILE_SIZE / (ray->distance * cos(
					ray->angle_rotation - cub->player.angle_rotation))
			) * (WINDOW_WIDTH / 2) / tan((FOV_DEGREE * (PI / 180) / 2));
	render_ceiling(cub, cub->pos_x, wall_height);
	if (ray->is_hor && ray->is_facing_up)
		draw_texture_line(cub, ray, wall_height, cub->texture.no);
	else if (ray->is_hor && !ray->is_facing_up)
		draw_texture_line(cub, ray, wall_height, cub->texture.so);
	else if (!ray->is_hor && ray->is_facing_left)
		draw_texture_line(cub, ray, wall_height, cub->texture.we);
	else if (!ray->is_hor && !ray->is_facing_left)
		draw_texture_line(cub, ray, wall_height, cub->texture.ea);
	render_floor(cub, cub->pos_x, wall_height);
}
