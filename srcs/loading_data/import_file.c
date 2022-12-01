/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:47:14 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/29 13:43:07 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	count_map_line(t_cub *cub, size_t *i, size_t *count)
{
	size_t	empty_line;
	char	*trimmed_line;

	empty_line = 0;
	trimmed_line = 0;
	while (cub->data.file_data[*i + empty_line])
	{
		trimmed_line = ft_strtrim(cub->data.file_data[*i + empty_line], " ");
		if (!*trimmed_line)
			empty_line++;
		else
		{
			(*i) += empty_line;
			(*count) += empty_line;
			(*count)++;
			empty_line = 0;
			(*i)++;
		}
		free(trimmed_line);
	}
}

void	fill_map(t_cub *cub)
{
	size_t	i;
	size_t	count;

	i = cub->data.map_idx;
	count = 0;
	count_map_line(cub, &i, &count);
	if (!count)
		throw_error("no map found", NULL);
	cub->map = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		cub->map[i] = cub->data.file_data[cub->data.map_idx + i];
		i++;
	}
	cub->map[i] = 0;
}

void	import_map(t_cub *cub)
{
	size_t	i;
	size_t	empty_line;
	char	*trimmed_line;

	i = cub->data.map_idx;
	trimmed_line = 0;
	while (cub->data.file_data[i])
	{
		trimmed_line = ft_strtrim(cub->data.file_data[i], " ");
		if (*trimmed_line)
			break ;
		free(trimmed_line);
		trimmed_line = 0;
		i++;
	}
	cub->data.map_idx = i;
	if (trimmed_line)
		free(trimmed_line);
	fill_map(cub);
}

void	import_configs(t_cub *cub)
{
	size_t	i;

	i = 0;
	import_cardinal_direction(cub, &i, NO);
	import_cardinal_direction(cub, &i, SO);
	import_cardinal_direction(cub, &i, WE);
	import_cardinal_direction(cub, &i, EA);
	import_color(cub, &i, F_C);
	import_color(cub, &i, C_C);
	cub->data.map_idx = i;
	import_map(cub);
}

void	import_file(t_cub *cub, char *filename)
{
	cub->data.fd = open(filename, O_RDONLY);
	if (cub->data.fd < 0)
		throw_error(": inaccessible file", filename);
	import_data(cub);
	import_configs(cub);
}
