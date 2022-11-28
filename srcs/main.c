/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:37:34 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/28 12:06:52 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	throw_error(char *err, char *cause)
{
	char	*new_line;

	ft_putstr_fd(RED"Error: "RESET, 2);
	if (cause)
	{
		new_line = ft_strchr(cause, '\n');
		if (new_line)
			*new_line = 0;	
		ft_putstr_fd(cause, 2);
	}
	ft_putendl_fd(err, 2);
	exit(1);
}

int is_cardinal_directions(char *line, size_t i)
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
	if (line[i] == 'F' &&
		(!line[i + 1] || line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (F_C);
	else if (line[i] == 'C' &&
		(!line[i + 1] || line[i + 1] == ' ' || line[i + 1] == '\t'))
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
		sym = is_cardinal_directions(line , i);
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
	char *line;
	char *data;
	char *shifter;

	line = "";
	data = ft_strdup("");
	while (line)
	{
		line = get_next_line(cub->data.fd);
		if (!line)
			break ;
		shifter = data;
		data = ft_strjoin(shifter, line);
		free(shifter);
		free(line);
	}
	cub->data.file_data = ft_split(data, '\n');
	free(data);
}
// throw_error(": Undefined symbol", NULL);

void	import_cardinal_direction(t_cub *cub, size_t *idx, int sym)
{
	char *checker;

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
			(*idx)++;
			break ;
		}
		free(checker);
		(*idx)++;
	}
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
}

void	import_file(t_cub *cub, char *filename)
{
	cub->data.fd = open(filename, O_RDONLY);
	if (cub->data.fd < 0)
		throw_error(": Inaccessible file", filename);
	import_data(cub);
	import_configs(cub);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		throw_error("Invalid Arguments", NULL);
	import_file(&cub, av[1]);
	return (0);
}
