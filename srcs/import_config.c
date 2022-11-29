/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:48:19 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/29 09:00:38 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	import_color(t_cub *cub, size_t *idx, int sym)
{
	char	*checker;

	if (!cub->data.file_data[*idx])
		throw_error("Color not found", NULL);
	checker = 0;
	while (cub->data.file_data[*idx])
	{
		checker = ft_strtrim(cub->data.file_data[*idx], " \t");
		if (*checker)
		{
			if (find_symbol(cub->data.file_data[*idx]) != sym)
				throw_error(": Color not found", cub->data.file_data[*idx]);
			if (sym == F_C)
				cub->data.floor_color = cub->data.file_data[*idx];
			else
				cub->data.ceiling_color = cub->data.file_data[*idx];
			(*idx)++;
			break ;
		}
		free(checker);
		(*idx)++;
	}
}

void	import_symbol(t_cub *cub, int symbol, char *line)
{
	size_t	i;
	char	**target;

	i = 0;
	while (line[i] && line[i] != '.' && line[i] != '/')
		i++;
	if (!line[i])
		throw_error(": Path not found", line);
	target = pointer_to_target_symbol(cub, symbol);
	*target = ft_strdup(&line[i]);
}

void	import_data(t_cub *cub)
{
	char	*line;
	char	*data;
	char	*shifter;

	line = "";
	data = ft_strdup("");
	while (line)
	{
		line = get_next_line(cub->data.fd);
		if (!line)
			break ;
		else if (*line == '\n')
		{
			free(line);
			line = ft_strdup(" \n");
		}
		shifter = data;
		data = ft_strjoin(shifter, line);
		free(shifter);
		free(line);
	}
	cub->data.file_data = ft_split(data, '\n');
	free(data);
}

void	import_cardinal_direction(t_cub *cub, size_t *idx, int sym)
{
	char	*checker;

	if (!cub->data.file_data[*idx])
		throw_error("Texture not found", NULL);
	checker = 0;
	while (cub->data.file_data[*idx])
	{
		checker = ft_strtrim(cub->data.file_data[*idx], " \t");
		if (*checker)
		{
			if (find_symbol(cub->data.file_data[*idx]) != sym)
				throw_error(": Texture not found", cub->data.file_data[*idx]);
			import_symbol(cub, sym, cub->data.file_data[*idx]);
			(*idx)++;
			break ;
		}
		free(checker);
		(*idx)++;
	}
}
