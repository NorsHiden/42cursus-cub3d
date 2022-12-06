/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:04:35 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/05 18:52:29 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	calc_vertical_line(t_cub *cub, t_fcord *intercept, t_ray *ray)
{
	while ((int)floor(intercept->y / TILE_SIZE) > 0
		&& (int)floor(intercept->y / TILE_SIZE) < cub->map_height
		&& (int)floor(intercept->x / TILE_SIZE) > 0
		&& (int)floor(intercept->x / TILE_SIZE) < cub->map_width)
	{
		if (!ray->is_facing_left && cub->map
			[(int)floor((intercept->y / TILE_SIZE))]
			[(int)floor(intercept->x / TILE_SIZE)] == '1')
			break ;
		else if (ray->is_facing_left && cub->map
			[(int)floor((intercept->y / TILE_SIZE))]
			[(int)floor(intercept->x / TILE_SIZE) - 1] == '1')
			break ;
		if (!ray->is_facing_left)
			intercept->x += TILE_SIZE;
		else
			intercept->x -= TILE_SIZE;
		intercept->y = cub->player.y
			+ (intercept->x - cub->player.x) * tan(ray->angle_rotation);
	}
}

t_fcord	get_vertical_intersection(t_cub *cub, t_ray *ray)
{
	t_fcord	intercept;

	intercept.x = floor(cub->player.x / TILE_SIZE) * TILE_SIZE;
	if (!ray->is_facing_left)
		intercept.x += TILE_SIZE;
	intercept.y = cub->player.y
		+ (intercept.x - cub->player.x) * tan(ray->angle_rotation);
	calc_vertical_line(cub, &intercept, ray);
	return (intercept);
}

void	setup_ray(t_ray *ray, t_fcord *intercept, double distance, int is_hor)
{
	ray->x = intercept->x;
	ray->y = intercept->y;
	ray->distance = distance;
	ray->is_hor = is_hor;
}

void	cast_ray(t_cub *cub, double angle, int idx)
{
	t_ray	*ray;
	t_fcord	hor_intercept;
	t_fcord	ver_intercept;
	double	hor_dis;
	double	ver_dis;

	ray = &cub->rays[idx];
	ray->angle_rotation = angle;
	ray->is_facing_up = (ray->angle_rotation > PI
			&& ray->angle_rotation < 2 * PI);
	ray->is_facing_left = (ray->angle_rotation > PI / 2
			&& ray->angle_rotation < 3 * PI / 2);
	hor_intercept = get_horizontal_intersection(cub, ray);
	ver_intercept = get_vertical_intersection(cub, ray);
	hor_dis = sqrt(pow(hor_intercept.x - cub->player.x, 2)
			+ pow(hor_intercept.y - cub->player.y, 2));
	ver_dis = sqrt(pow(ver_intercept.x - cub->player.x, 2)
			+ pow(ver_intercept.y - cub->player.y, 2));
	if (hor_dis < ver_dis)
		setup_ray(ray, &hor_intercept, hor_dis, 1);
	else
		setup_ray(ray, &ver_intercept, ver_dis, 0);
}

void	update_rays(t_cub *cub)
{
	double	angle;
	int		i;

	angle = cub->player.angle_rotation - (FOV_DEGREE * (PI / 180)) / 2;
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		if (angle < 0)
			angle += 2 * PI;
		else if (angle > 2 * PI)
			angle -= 2 * PI;
		cast_ray(cub, angle, i);
		angle += (FOV_DEGREE * (PI / 180)) / WINDOW_WIDTH;
		i++;
	}
}
