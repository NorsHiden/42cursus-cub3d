/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:03:10 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/05 18:31:17 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	display_minimap(t_cub *cub)
{
	draw_minimap(cub);
	draw_rays(cub);
	draw_player(cub);
	render_layer(cub);
}

void	launch_game(t_cub *cub)
{
	cub->settings.window = mlx_new_window(
			cub->settings.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	cub->settings.frame = mlx_new_image(
			cub->settings.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->settings.frame_addr = mlx_get_data_addr(cub->settings.frame,
			&cub->settings.frame_bits_per_pixel,
			&cub->settings.frame_size_line, &cub->settings.frame_endian);
	cub->map_width = ft_strlen(cub->map[0]);
	cub->map_height = ptrlen(cub->map);
	cub->settings.minimap_layer = mlx_new_image(
			cub->settings.mlx, cub->map_width * TILE_SIZE,
			cub->map_height * TILE_SIZE);
	cub->settings.minimap_layer_addr = mlx_get_data_addr(
			cub->settings.minimap_layer,
			&cub->settings.minimap_bits_per_pixel,
			&cub->settings.minimap_size_line, &cub->settings.minimap_endian);
	setup_player(cub);
	update_rays(cub);
	display_3dmap(cub);
	display_minimap(cub);
	mlx_put_image_to_window(cub->settings.mlx,
		cub->settings.window, cub->settings.frame, 0, 0);
	mlx_hook(cub->settings.window, 2, 0, key_pressed, cub);
	mlx_loop(cub->settings.mlx);
}
