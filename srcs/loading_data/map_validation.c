/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:29:56 by nelidris          #+#    #+#             */
/*   Updated: 2022/12/01 09:55:40 by nelidris         ###   ########.fr       */
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

void	check_symbol_sensitivity(char **map, size_t y, size_t x, char sym)
{
	if (map[y][x] != sym)
		return ;
	if (y == 0 || x == 0 || y == ptrlen(map) - 1 || x == ft_strlen(map[y] - 1))
		throw_error(": invalid map design", map[y]);
	if (x > 0 && (!ft_strchr("01NSWE", map[y][x - 1])
		|| !ft_strchr("01NSWE", map[y][x + 1])))
		throw_error(": invalid map design", map[y]);
	if (y > 0 && (!ft_strchr("01NSWE", map[y - 1][x])
		|| !ft_strchr("01NSWE", map[y + 1][x])))
		throw_error(": invalid map design", map[y]);
}

void	assign_player_orientation(char sym, int *player_orientation)
{
	if (sym == 'N')
	{
		if (*player_orientation)
			throw_error("multiple player positions", NULL);
		*player_orientation = NO;
	}
	else if (sym == 'S')
	{
		if (*player_orientation)
			throw_error("multiple player positions", NULL);
		*player_orientation = SO;
	}
	else if (sym == 'W')
	{
		if (*player_orientation)
			throw_error("multiple player positions", NULL);
		*player_orientation = WE;
	}
	else if (sym == 'E')
	{
		if (*player_orientation)
			throw_error("multiple player positions", NULL);
		*player_orientation = EA;
	}
}

void	check_line_validation(char **map, int *player_orientation, size_t y)
{
	size_t	x;
	char	*sym;

	x = 0;
	while (map[y][x])
	{
		if (map[y][x] == '0')
			check_symbol_sensitivity(map, y, x, '0');
		sym = ft_strchr("NSWE", map[y][x]);
		if (sym)
		{
			check_symbol_sensitivity(map, y, x, *sym);
			assign_player_orientation(*sym, player_orientation);
		}
		x++;
	}
}

void	map_valid(t_cub *cub)
{
	size_t	y;

	y = 0;
	cub->player_orientation = 0;
	while (cub->map[y])
		check_line_validation(cub->map, &cub->player_orientation, y++);
}
