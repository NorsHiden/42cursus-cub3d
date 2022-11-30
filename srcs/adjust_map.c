/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:55:45 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/30 08:29:49 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	valid_map_symbol(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == ' '
		|| c == 'S' || c == 'E' || c == 'W');
}

static void	enlarge_line(char **line, size_t new_size)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(sizeof(char) * (new_size + 1));
	i = 0;
	while ((*line)[i])
	{
		if (!valid_map_symbol((*line)[i]))
			throw_error("invalid map symbol", NULL);
		new_line[i] = (*line)[i];
		i++;
	}
	while (i < new_size)
		new_line[i++] = ' ';
	new_line[i] = 0;
	*line = new_line;
}

static int	find_big_size(char **map)
{
	size_t	i;
	size_t	big_size;
	size_t	len;

	big_size = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > big_size)
			big_size = len;
		i++;
	}
	return (big_size);
}

void	adjust_map_size(t_cub *cub)
{
	size_t	i;
	size_t	big_size;

	i = 0;
	big_size = find_big_size(cub->map);
	while (cub->map[i])
		enlarge_line(&cub->map[i++], big_size);
	map_valid(cub);
}
