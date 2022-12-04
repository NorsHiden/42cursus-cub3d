/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/04 13:05:12 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>



void	display_minimap(t_cub *cub)
{
	draw_minimap(cub);
	update_rays(cub);
	draw_player(cub);
}

void reset_frame(t_cub *cub)
{
	t_cord pos;

	pos.y = 0;
	while (pos.y < WINDOW_HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WINDOW_WIDTH)
			draw_pixel(cub, pos.x++, pos.y, 0);
		pos.y++;
	}
}

void	launch_game(t_cub *cub)
{
	cub->settings.window = mlx_new_window(cub->settings.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	cub->settings.frame = mlx_new_image(cub->settings.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->settings.frame_addr = mlx_get_data_addr(cub->settings.frame,
			&cub->settings.bits_per_pixel, &cub->settings.size_line, &cub->settings.endian);
	cub->map_width = ft_strlen(cub->map[0]);
	cub->map_height = ptrlen(cub->map);
	setup_player(cub);
	cub->start.x = /*20;*/ (WINDOW_WIDTH / 2) - ((ft_strlen(cub->map[0]) * MAP_TILE_SIZE) / 2);
	cub->start.y = /*(WINDOW_HEIGHT - ptrlen(cub->map) * MAP_TILE_SIZE) - 20;*/ (WINDOW_HEIGHT / 2) - ((ptrlen(cub->map) * MAP_TILE_SIZE) / 2);
	display_minimap(cub);
	mlx_put_image_to_window(cub->settings.mlx, cub->settings.window, cub->settings.frame, 0, 0);
	mlx_hook(cub->settings.window, 2, 0, key_pressed, cub);
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
