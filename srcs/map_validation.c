/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:29:56 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/30 09:03:49 by nelidris         ###   ########.fr       */
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

void	check_line_validation(char **map, size_t y)
{
	size_t	x;

	x = 0;
	while (map[y][x])
	{
		check_symbol_sensitivity(map, y, x, '0');
		check_symbol_sensitivity(map, y, x, 'N');
		check_symbol_sensitivity(map, y, x, 'S');
		check_symbol_sensitivity(map, y, x, 'W');
		check_symbol_sensitivity(map, y, x, 'E');
		x++;
	}
}

void	map_valid(t_cub *cub)
{
	size_t	y;

	y = 0;
	while (cub->map[y])
		check_line_validation(cub->map, y++);
}
