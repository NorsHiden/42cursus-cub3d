/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:50:55 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/29 08:59:50 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_cardinal_directions(char *line, size_t i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		if (!line[i + 2] || line[i + 2] == ' ' || line[i + 2] == '\t')
			return (NO);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		if (!line[i + 2] || line[i + 2] == ' ' || line[i + 2] == '\t')
			return (SO);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		if (!line[i + 2] || line[i + 2] == ' ' || line[i + 2] == '\t')
			return (WE);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		if (!line[i + 2] || line[i + 2] == ' ' || line[i + 2] == '\t')
			return (EA);
	}
	return (0);
}

int	is_rgb(char *line, size_t i)
{
	if (line[i] == 'F'
		&& (!line[i + 1] || line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (F_C);
	else if (line[i] == 'C'
		&& (!line[i + 1] || line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (C_C);
	return (0);
}

int	find_symbol(char *line)
{
	size_t	i;
	int		sym;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i])
	{
		sym = is_cardinal_directions(line, i);
		if (sym)
			return (sym);
		sym = is_rgb(line, i);
		if (sym)
			return (sym);
	}
	return (0);
}

char	**pointer_to_target_symbol(t_cub *cub, int symbol)
{
	if (symbol == NO)
		return (&cub->data.no_filename);
	else if (symbol == SO)
		return (&cub->data.so_filename);
	else if (symbol == WE)
		return (&cub->data.we_filename);
	else if (symbol == EA)
		return (&cub->data.ea_filename);
	return (0);
}
