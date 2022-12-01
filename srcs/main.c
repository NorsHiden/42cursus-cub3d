/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/01 09:55:36 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		throw_error("invalid Arguments", NULL);
	import_file(&cub, av[1]);
	cub.mlx = mlx_init();
	import_texture(&cub);
	adjust_map_size(&cub);
	return (0);
}
