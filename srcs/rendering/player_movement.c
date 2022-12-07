/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:04:50 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:28:10 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	go_through_wall(char *b_x, char *b_y, char *a_x, char *a_y)
{
	if (*b_y == '1' && *b_x == '1' && b_y == a_x && b_x == a_y)
		return (1);
	return (0);
}

int	vertical_wall_collision(t_cub *cub, double next_x, double next_y)
{
	if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)]
		[(int)(cub->player.x / TILE_SIZE) + 1],
		&cub->map[(int)((cub->player.y) / TILE_SIZE) - 1]
		[(int)(cub->player.x / TILE_SIZE)],
		&cub->map[(int)(next_y / TILE_SIZE)]
		[(int)(next_x / TILE_SIZE) - 1],
		&cub->map[(int)(next_y / TILE_SIZE) + 1]
		[(int)(next_x / TILE_SIZE)]))
		return (1);
	else if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)]
		[(int)(cub->player.x / TILE_SIZE) - 1],
		&cub->map[(int)((cub->player.y) / TILE_SIZE) - 1]
		[(int)(cub->player.x / TILE_SIZE)],
		&cub->map[(int)(next_y / TILE_SIZE)]
		[(int)(next_x / TILE_SIZE) + 1],
		&cub->map[(int)(next_y / TILE_SIZE) + 1]
		[(int)(next_x / TILE_SIZE)]))
		return (1);
	return (0);
}

int	horizontal_wall_collision(t_cub *cub, double next_x, double next_y)
{
	if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)]
		[(int)(cub->player.x / TILE_SIZE) + 1],
		&cub->map[(int)((cub->player.y) / TILE_SIZE) + 1]
		[(int)(cub->player.x / TILE_SIZE)],
		&cub->map[(int)(next_y / TILE_SIZE)]
		[(int)(next_x / TILE_SIZE) - 1],
		&cub->map[(int)(next_y / TILE_SIZE) - 1]
		[(int)(next_x / TILE_SIZE)]))
		return (1);
	else if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)]
		[(int)(cub->player.x / TILE_SIZE) - 1],
		&cub->map[(int)((cub->player.y) / TILE_SIZE) + 1]
		[(int)(cub->player.x / TILE_SIZE)],
		&cub->map[(int)(next_y / TILE_SIZE)]
		[(int)(next_x / TILE_SIZE) + 1],
		&cub->map[(int)(next_y / TILE_SIZE) - 1]
		[(int)(next_x / TILE_SIZE)]))
		return (1);
	return (0);
}

int	move_or_not(t_cub *cub, double next_x, double next_y)
{
	if (cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] == '0'
		&& &cub->map[(int)(cub->player.y / TILE_SIZE)]
		[(int)(cub->player.x / TILE_SIZE)]
		!= &cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)])
	{
		if (vertical_wall_collision(cub, next_x, next_y)
			|| horizontal_wall_collision(cub, next_x, next_y))
			return (0);
	}
	if (cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] == '0')
		return (1);
	return (2);
}

int	key_pressed(int key, t_cub *cub)
{
	if (key == ESC)
		exit(0);
	move_up(key, cub);
	move_down(key, cub);
	move_left(key, cub);
	move_right(key, cub);
	if (key == LEFT_ARR)
		cub->player.angle_rotation -= 4 * (PI / 180);
	else if (key == RIGHT_ARR)
		cub->player.angle_rotation += 4 * (PI / 180);
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
