/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/05 18:20:04 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line_frame(t_cub *cub, t_cord start, t_cord end, int color)
{
	t_fcord	middle;
	t_fcord	d_middle;
	double	distance;

	middle.x = 0;
	middle.y = 0;
	distance = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	d_middle.x = (end.x - start.x) / distance;
	d_middle.y = (end.y - start.y) / distance;
	while (distance-- > 0)
	{
		draw_pixel_frame(cub, start.x + middle.x, start.y + middle.y, color);
		middle.x += d_middle.x;
		middle.y += d_middle.y;
	}
}

int	get_color_from_texture(void *texture, int x, int y, double wall_height)
{
	char	*texture_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	texture_addr = mlx_get_data_addr(texture,
			&bits_per_pixel, &size_line, &endian);
	return (*(int *)(texture_addr
		+ ((int)(y * (TILE_SIZE / wall_height)) *size_line
		+ (x % TILE_SIZE) * (bits_per_pixel / 8))));
}

void	draw_texture_line(t_cub *cub, t_ray	*ray,
	double wall_height, void *texture)
{
	int	color;
	int	y;
	int	end;

	y = 0;
	if (wall_height > WINDOW_HEIGHT)
	{
		y = wall_height / 2 - WINDOW_HEIGHT / 2;
		end = wall_height / 2 + WINDOW_HEIGHT / 2;
	}
	else
		end = wall_height;
	while (y < end)
	{
		if (ray->is_hor)
			color = get_color_from_texture(texture, ray->x, y, wall_height);
		else
			color = get_color_from_texture(texture, ray->y, y, wall_height);
		draw_pixel_frame(cub, cub->pos_x,
			(WINDOW_HEIGHT / 2 - wall_height / 2 + y), color);
		y++;
	}
}

void	render_ceiling(t_cub *cub, int x, double wall_height)
{
	int	y;
	int	end;

	y = 0;
	end = (WINDOW_HEIGHT / 2) - wall_height / 2;
	while (y < end)
	{
		draw_pixel_frame(cub, x, y, cub->texture.ceiling);
		y++;
	}
}

void	render_floor(t_cub *cub, int x, double wall_height)
{
	int	y;
	int	end;

	y = WINDOW_HEIGHT / 2 + wall_height / 2;
	end = WINDOW_HEIGHT;
	while (y < end)
	{
		draw_pixel_frame(cub, x, y, cub->texture.floor);
		y++;
	}
}

void	render_ray(t_cub *cub, t_ray *ray)
{
	double	wall_height;

	wall_height = (TILE_SIZE / (ray->distance * cos(ray->angle_rotation - cub->player.angle_rotation))) * (WINDOW_WIDTH / 2) / tan((FOV_DEGREE * (PI / 180) / 2));
	render_ceiling(cub, cub->pos_x, wall_height);
	if (ray->is_hor && ray->is_facing_up)
		draw_texture_line(cub, ray, wall_height, cub->texture.no);
	else if (ray->is_hor && !ray->is_facing_up)
		draw_texture_line(cub, ray, wall_height, cub->texture.so);
	else if (!ray->is_hor && ray->is_facing_left)
		draw_texture_line(cub, ray, wall_height, cub->texture.we);
	else if (!ray->is_hor && !ray->is_facing_left)
		draw_texture_line(cub, ray, wall_height, cub->texture.ea);
	render_floor(cub, cub->pos_x, wall_height);
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

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		throw_error("invalid Arguments", NULL);
	import_file(&cub, av[1]);
	cub.settings.mlx = mlx_init();
	import_texture(&cub);
	cub.start.x = 20;
	cub.start.y = 20;
	launch_game(&cub);
	return (0);
}
