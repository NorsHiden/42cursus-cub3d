/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:04:50 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/06 08:09:40 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	move_or_not(t_cub *cub, double x, double y)
{
	return (cub->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '0');
}

static void	move_ver(int key, t_cub *cub)
{
	if (key == UP && move_or_not(cub, cub->player.x
			+ cos(cub->player.angle_rotation) * PPM, cub->player.y
			+ sin(cub->player.angle_rotation) * PPM))
	{
		cub->player.x += cos(cub->player.angle_rotation) * PPM;
		cub->player.y += sin(cub->player.angle_rotation) * PPM;
	}
	else if (key == DOWN && move_or_not(cub, cub->player.x
			- cos(cub->player.angle_rotation) * PPM, cub->player.y
			- sin(cub->player.angle_rotation) * PPM))
	{
		cub->player.x -= cos(cub->player.angle_rotation) * PPM;
		cub->player.y -= sin(cub->player.angle_rotation) * PPM;
	}
}

static void	move_hor(int key, t_cub *cub)
{
	if (key == LEFT && move_or_not(cub, cub->player.x
			- cos(cub->player.angle_rotation + PI / 2) * PPM, cub->player.y
			- sin(cub->player.angle_rotation + PI / 2) * PPM))
	{
		cub->player.x -= cos(cub->player.angle_rotation + PI / 2) * PPM;
		cub->player.y -= sin(cub->player.angle_rotation + PI / 2) * PPM;
	}
	else if (key == RIGHT && move_or_not(cub, cub->player.x
			+ cos(cub->player.angle_rotation + PI / 2) * PPM, cub->player.y
			+ sin(cub->player.angle_rotation + PI / 2) * PPM))
	{
		cub->player.x += cos(cub->player.angle_rotation + PI / 2) * PPM;
		cub->player.y += sin(cub->player.angle_rotation + PI / 2) * PPM;
	}
}

int	key_pressed(int key, t_cub *cub)
{
	move_ver(key, cub);
	move_hor(key, cub);
	if (key == LEFT_ARR)
		cub->player.angle_rotation -= 6 * (PI / 180);
	else if (key == RIGHT_ARR)
		cub->player.angle_rotation += 6 * (PI / 180);
	if (cub->player.angle_rotation > 2 * PI)
		cub->player.angle_rotation -= 2 * PI;
	else if (cub->player.angle_rotation < 0)
		cub->player.angle_rotation += 2 * PI;
	update_rays(cub);
	display_3dmap(cub);
	display_minimap(cub);
	mlx_put_image_to_window(cub->settings.mlx,
		cub->settings.window, cub->settings.frame, 0, 0);
	return (0);
}
