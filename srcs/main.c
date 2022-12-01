/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/01 08:55:27 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

size_t	ptrlen(char **str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

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
