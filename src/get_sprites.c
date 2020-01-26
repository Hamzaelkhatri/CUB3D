/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:16:54 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int				returns(char *msg)
{
	ft_putstr(msg);
	exit(0);
}

unsigned long	rgb_to_hex(int r, int g, int b)
{
	return (24 << 24 | r << 16) | (g << 8) | (b << 0);
}

void			get_sprite(t_params *params)
{
	int		i;
	int		v;
	char	*line;

	i = 2;
	v = 0;
	get_next_line(params->fd, &line);
	get_next_line(params->fd, &line);
	if (line[0] == 'S')
	{
		if (!(params->path_sprite = malloc(sizeof(int) * ft_strlen(line))))
			returns("Error\n");
		if (line[i] != '\0')
		{
			while (line[i] == ' ')
				i++;
			ft_strlcpy(params->path_sprite, &line[i]);
		}
	}
	else
		returns("Error\nCHECK THE PATH OF SPRITE");
}
