/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:19:22 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 13:21:47 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_up(int key, t_cub *cub)
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
				cub->player.x = cub->player.x
					+ cos(cub->player.angle_rotation) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y
					+ sin(cub->player.angle_rotation) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}

void	move_down(int key, t_cub *cub)
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
				cub->player.x = cub->player.x
					- cos(cub->player.angle_rotation) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y
					- sin(cub->player.angle_rotation) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}

void	move_left(int key, t_cub *cub)
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
				cub->player.x = cub->player.x
					- cos(cub->player.angle_rotation + PI / 2) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y
					- sin(cub->player.angle_rotation + PI / 2) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}

void	move_right(int key, t_cub *cub)
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
				cub->player.x = cub->player.x
					+ cos(cub->player.angle_rotation + PI / 2) * (PPM / 2);
			else if (move_or_not(cub, cub->player.x, new_y) == 1)
				cub->player.y = cub->player.y
					+ sin(cub->player.angle_rotation + PI / 2) * (PPM / 2);
		}
		else
		{
			cub->player.x = new_x;
			cub->player.y = new_y;
		}
	}
}
