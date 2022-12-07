/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:04:50 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 11:11:01 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	go_through_wall(char *b_x, char *b_y, char *a_x, char *a_y)
{
	if (*b_y == '1' && *b_x == '1' && b_y == a_x && b_x == a_y)
		return (1);
	return (0);
}

static int	move_or_not(t_cub *cub, double next_x, double next_y)
{
	if (cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] == '0'
		&& &cub->map[(int)(cub->player.y / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE)]
		!= &cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)])
	{
		if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE) + 1],
			&cub->map[(int)((cub->player.y) / TILE_SIZE) - 1][(int)(cub->player.x / TILE_SIZE)],
			&cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE) - 1],
			&cub->map[(int)(next_y / TILE_SIZE) + 1][(int)(next_x / TILE_SIZE)])) //UP_RIGHT
			return (0);
		else if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE) - 1],
			&cub->map[(int)((cub->player.y) / TILE_SIZE) - 1][(int)(cub->player.x / TILE_SIZE)],
			&cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE) + 1],
			&cub->map[(int)(next_y / TILE_SIZE) + 1][(int)(next_x / TILE_SIZE)])) //UP_LEFT
			return (0);
		else if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE) + 1],
			&cub->map[(int)((cub->player.y) / TILE_SIZE) + 1][(int)(cub->player.x / TILE_SIZE)],
			&cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE) - 1],
			&cub->map[(int)(next_y / TILE_SIZE) - 1][(int)(next_x / TILE_SIZE)])) //DOWN_RIGHT
			return (0);
		else if (go_through_wall(&cub->map[(int)((cub->player.y) / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE) - 1],
			&cub->map[(int)((cub->player.y) / TILE_SIZE) + 1][(int)(cub->player.x / TILE_SIZE)],
			&cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE) + 1],
			&cub->map[(int)(next_y / TILE_SIZE) - 1][(int)(next_x / TILE_SIZE)])) //DOWN_LEFT
			return (0);
	}
	if (cub->map[(int)(next_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] == '0')
		return (1);
	return (2);
}

static void	move_up(int key, t_cub *cub)
{
	double	new_x;
	double	new_y;
	int		des;

	new_x = cub->player.x + cos(cub->player.angle_rotation) * PPM;
	new_y = cub->player.y + sin(cub->player.angle_rotation) * PPM;
	des = move_or_not(cub, new_x, new_y);
	if (key == UP && des)
	{
		if (des == 2)
		{
			if (move_or_not(cub, new_x, cub->player.y) == 1)
				cub->player.x = cub->player.x + cos(cub->player.angle_rotation) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y + sin(cub->player.angle_rotation) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}

static void	move_down(int key, t_cub *cub)
{
	double	new_x;
	double	new_y;
	int		des;
	
	new_x = cub->player.x - cos(cub->player.angle_rotation) * PPM;
	new_y = cub->player.y - sin(cub->player.angle_rotation) * PPM;
	des = move_or_not(cub, new_x, new_y);
	if (key == DOWN && move_or_not(cub, new_x, new_y))
	{
		if (des == 2)
		{
			if (move_or_not(cub, new_x, cub->player.y) == 1)
				cub->player.x = cub->player.x - cos(cub->player.angle_rotation) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y - sin(cub->player.angle_rotation) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}

static void	move_left(int key, t_cub *cub)
{
	double	new_x;
	double	new_y;
	int		des;

	new_x = cub->player.x - cos(cub->player.angle_rotation + PI / 2) * PPM;
	new_y = cub->player.y - sin(cub->player.angle_rotation + PI / 2) * PPM;
	des = move_or_not(cub, new_x, new_y);
	if (key == LEFT && des)
	{
		if (des == 2)
		{
			if (move_or_not(cub, new_x, cub->player.y) == 1)
				cub->player.x = cub->player.x - cos(cub->player.angle_rotation + PI / 2) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y - sin(cub->player.angle_rotation + PI / 2) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}

static void	move_right(int key, t_cub *cub)
{
	double	new_x;
	double	new_y;
	int		des;
	
	new_x = cub->player.x + cos(cub->player.angle_rotation + PI / 2) * PPM;
	new_y = cub->player.y + sin(cub->player.angle_rotation + PI / 2) * PPM;
	des = move_or_not(cub, new_x, new_y);
	if (key == RIGHT && des)
	{
		if (des == 2)
		{
			if (move_or_not(cub, new_x, cub->player.y) == 1)
				cub->player.x = cub->player.x + cos(cub->player.angle_rotation + PI / 2) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y + sin(cub->player.angle_rotation + PI / 2) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
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
