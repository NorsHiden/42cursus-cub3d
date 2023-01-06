/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:58:07 by nelidris          #+#    #+#             */
/*   Updated: 2023/01/04 19:00:56 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_movement(int x, int y, t_cub *cub)
{	
	mlx_mouse_move(cub->settings.window,
		(WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));
	if (x - (WINDOW_WIDTH / 2) < 0)
		cub->player.angle_rotation -= 3 * (PI / 180);
	else if (x - (WINDOW_WIDTH / 2) > 0)
		cub->player.angle_rotation += 3 * (PI / 180);
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
