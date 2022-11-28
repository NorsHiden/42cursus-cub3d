/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 09:31:05 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/28 11:16:30 by nelidris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>

# define RED "\033[0;31m"
# define RESET "\033[0;37m"

# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F_C 5
# define C_C 6

typedef struct s_file_data
{
	int		fd;
	char	*no_filename;
	char	*so_filename;
	char	*we_filename;
	char	*ea_filename;
	char	*floor_color;
	char	*ceiling_color;
	char	**file_data;
} t_file_data;

typedef struct s_cub
{
	t_file_data	data;
}	t_cub;

#endif /* CUB3D_H */