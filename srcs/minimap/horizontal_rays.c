/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:20:14 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/04 13:20:45 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<cub3d.h>

static void	calc_horizontal_line(t_cub *cub, t_fcord *intercept, t_ray *ray)
{
	while ((int)floor(intercept->x / TILE_SIZE) > 0
		&& (int)floor(intercept->x / TILE_SIZE) < cub->map_width
		&& (int)floor(intercept->y / TILE_SIZE) > 0
		&& (int)floor(intercept->y / TILE_SIZE) < cub->map_height)
	{
		if (!ray->is_facing_up && cub->map
			[(int)floor((intercept->y / TILE_SIZE))]
			[(int)floor(intercept->x / TILE_SIZE)] == '1')
			break ;
		else if (ray->is_facing_up && cub->map
			[(int)floor((intercept->y / TILE_SIZE)) - 1]
			[(int)floor(intercept->x / TILE_SIZE)] == '1')
			break ;
		if (!ray->is_facing_up)
			intercept->y += TILE_SIZE;
		else
			intercept->y -= TILE_SIZE;
		intercept->x = cub->player.x
			+ (intercept->y - cub->player.y) / tan(ray->angle_rotation);
	}
}

t_fcord	get_horizontal_intersection(t_cub *cub, t_ray *ray)
{
	t_fcord	intercept;

	intercept.y = floor(cub->player.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->is_facing_up)
		intercept.y += TILE_SIZE;
	intercept.x = cub->player.x
		+ (intercept.y - cub->player.y) / tan(ray->angle_rotation);
	calc_horizontal_line(cub, &intercept, ray);
	return (intercept);
}
