/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/06 09:05:37 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>



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
