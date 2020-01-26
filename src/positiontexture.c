/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positiontexture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:40:07 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_no_texture(t_params *params)
{
	int		i;
	int		v;
	t_rgb	color;
	char	rgb[3];

	i = 2;
	v = 0;
	get_next_line(params->fd, &params->line);
	get_next_line(params->fd, &params->line);
	if (params->line[0] == 'N' && params->line[1] == 'O')
	{
		params->path_no = malloc(ft_strlen(params->line));
		if (params->line[i] != '\0')
		{
			while (params->line[i] == ' ')
				i++;
			ft_strlcpy(params->path_no, &params->line[i]);
		}
		free(params->line);
	}
	else
		returns("EROR\nCHECK THE PATH OF NO TEXTURE");
}

void	get_so_texture(t_params *params)
{
	int			i;
	int			v;
	t_rgb		color;
	char		rgb[3];

	i = 2;
	v = 0;
	get_next_line(params->fd, &params->line);
	if (params->line[0] == 'S' && params->line[1] == 'O')
	{
		params->path_so = malloc(ft_strlen(params->line));
		if (params->line[i] != '\0')
		{
			while (params->line[i] == ' ')
				i++;
			ft_strlcpy(params->path_so, &params->line[i]);
		}
		free(params->line);
	}
	else
		returns("EROR\nCHECK THE PATH OF SO TEXTURE");
}

void	get_we_texture(t_params *params)
{
	int		i;
	int		v;
	t_rgb	color;
	char	rgb[3];

	i = 2;
	v = 0;
	get_next_line(params->fd, &params->line);
	if (params->line[0] == 'W' && params->line[1] == 'E')
	{
		params->path_we = malloc(ft_strlen(params->line));
		if (params->line[i] != '\0')
		{
			while (params->line[i] == ' ')
				i++;
			ft_strlcpy(params->path_we, &params->line[i]);
		}
		free(params->line);
	}
	else
		returns("EROR\nCHECK THE PATH OF SO TEXTURE");
}

void	get_ea_texture(t_params *params)
{
	int		i;
	int		v;
	t_rgb	color;
	char	rgb[3];

	i = 2;
	v = 0;
	get_next_line(params->fd, &params->line);
	if (params->line[0] == 'E' && params->line[1] == 'A')
	{
		params->path_es = malloc(ft_strlen(params->line));
		if (params->line[i] != '\0')
		{
			while (params->line[i] == ' ')
				i++;
			ft_strlcpy(params->path_es, &params->line[i]);
		}
		free(params->line);
	}
	else
		returns("EROR\nCHECK THE PATH OF EA TEXTURE");
}
