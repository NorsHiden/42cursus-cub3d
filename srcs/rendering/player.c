/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:37:44 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 08:44:42 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_player(t_cub *cub)
{
	t_cord	pos;

	pos.y = (PLAYER_SIZE * -1) + (PLAYER_SIZE / 2);
	while (pos.y < 4)
	{
		pos.x = (PLAYER_SIZE * -1) + (PLAYER_SIZE / 2);
		while (pos.x < 4)
		{
			draw_pixel(cub, ((cub->player.x * LARGE_TO_SMALL_SCALE)
				+ pos.x++), ((cub->player.y * LARGE_TO_SMALL_SCALE)
				+ pos.y), 0xBF7E78);
		}
		pos.y++;
	}
}

void	fill_player(t_cub *cub, t_cord pos)
{
	cub->player.x = (pos.x * TILE_SIZE) + TILE_SIZE / 2;
	cub->player.y = (pos.y * TILE_SIZE) + TILE_SIZE / 2;
	if (cub->player_orientation == NO)
		cub->player.angle_rotation = (3 * PI) / 2;
	else if (cub->player_orientation == SO)
		cub->player.angle_rotation = PI / 2;
	else if (cub->player_orientation == WE)
		cub->player.angle_rotation = PI;
	else
		cub->player.angle_rotation = 0;
}

void	setup_player(t_cub *cub)
{
	t_cord	pos;

	pos.y = 0;
	while (cub->map[pos.y])
	{
		pos.x = 0;
		while (cub->map[pos.y][pos.x])
		{
			if (ft_strchr("NSWE", cub->map[pos.y][pos.x]))
			{
				fill_player(cub, pos);
				cub->map[pos.y][pos.x] = '0';
				return ;
			}
			pos.x++;
		}
		pos.y++;
	}
	if (!cub->map[pos.y])
		throw_error("player not found", NULL);
}
