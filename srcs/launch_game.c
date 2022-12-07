/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:03:10 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/07 11:47:47 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	frame_color(t_cub *cub, int x, int y)
{
	char	*frame_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	frame_addr = mlx_get_data_addr(cub->texture.frame, &bits_per_pixel, &size_line, &endian);
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
	mlx_mouse_move(cub->settings.window, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));
	mlx_mouse_hide(cub->settings.window);
	mlx_hook(cub->settings.window, 2, 0, key_pressed, cub);
	mlx_hook(cub->settings.window, 17, 0, quit_cub3d, cub);
	mlx_hook(cub->settings.window, 6, 0, mouse_movement, cub);
	mlx_loop(cub->settings.mlx);
}
