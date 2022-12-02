/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/02 09:24:21 by nelidris         ###   ########.fr       */
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

void	draw_square(t_cub *cub, t_cord pos, t_cord *start, int color)
{
	t_cord	f;

	f.y = 0;
	while (f.y < MAP_TILE_SIZE)
	{
		f.x = 0;
		while (f.x < MAP_TILE_SIZE)
			draw_pixel(cub, ((pos.x * MAP_TILE_SIZE) + start->x + f.x++),
				((pos.y * MAP_TILE_SIZE) + start->y + f.y), color);
		f.y++;
	}
}

void	draw_player(t_cub *cub, t_cord *start)
{
	t_cord	pos;

	pos.y = (PLAYER_SIZE * -1) + (PLAYER_SIZE / 2);
	while (pos.y < 4)
	{
		pos.x = (PLAYER_SIZE * -1) + (PLAYER_SIZE / 2);
		while (pos.x < 4)
		{
			draw_pixel(cub, ((cub->player.x * LARGE_TO_SMALL_SCALE)
					+ start->x + pos.x++), ((cub->player.y
						* LARGE_TO_SMALL_SCALE)
					+ start->y + pos.y), 0xFF0000);
		}
		pos.y++;
	}
}

void	draw_minimap(t_cub *cub, t_cord *start)
{
	t_cord	pos;

	pos.y = 0;
	while (cub->map[pos.y])
	{
		pos.x = 0;
		while (cub->map[pos.y][pos.x])
		{
			if (cub->map[pos.y][pos.x] == '1')
				draw_square(cub, pos, start, 0xFFFFFF);
			else if (ft_strchr("0NSWE", cub->map[pos.y][pos.x]))
				draw_square(cub, pos, start, 0xAAAAAA);
			pos.x++;
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
				return ;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	display_minimap(t_cub *cub, t_cord *start)
{
	draw_minimap(cub, start);
	draw_player(cub, start);
}

void	launch_game(t_cub *cub)
{
	t_cord	start;

	cub->settings.window = mlx_new_window(cub->settings.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	cub->settings.frame = mlx_new_image(cub->settings.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->settings.frame_addr = mlx_get_data_addr(cub->settings.frame,
			&cub->settings.bits_per_pixel, &cub->settings.size_line, &cub->settings.endian);
	setup_player(cub);
	start.x = /*20;*/ (WINDOW_WIDTH / 2) - ((ft_strlen(cub->map[0]) * MAP_TILE_SIZE) / 2);
	start.y = /*(WINDOW_HEIGHT - ptrlen(cub->map) * MAP_TILE_SIZE) - 20;*/ (WINDOW_HEIGHT / 2) - ((ptrlen(cub->map) * MAP_TILE_SIZE) / 2);
	display_minimap(cub, &start);
	mlx_put_image_to_window(cub->settings.mlx, cub->settings.window, cub->settings.frame, 0, 0);
	mlx_loop(cub->settings.mlx);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		throw_error("invalid Arguments", NULL);
	import_file(&cub, av[1]);
	cub.settings.mlx = mlx_init();
	import_texture(&cub);
	launch_game(&cub);
	return (0);
}
