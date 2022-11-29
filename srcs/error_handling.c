/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelidris <nelidris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:49:50 by nelidris          #+#    #+#             */
/*   Updated: 2022/11/29 08:57:30 by nelidris         ###   ########.fr       */
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
