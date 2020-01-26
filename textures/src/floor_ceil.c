/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:26:41 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_val(t_params *params, t_rgb *color, int v, char *rgb)
{
	if (v == 2)
		color->b = ft_atoi(rgb);
}

void	ft_cval(t_params *params, int v, char *rgb, t_rgb *color)
{
	if (v == 0)
		color->r = ft_atoi(rgb);
	else if (v == 1)
		color->g = ft_atoi(rgb);
}

int		ciel_values(t_params *params, t_rgb *color, int v)
{
	int		i;
	char	rgb[3];
	int		c;

	i = 0;
	c = 0;
	while (params->line[i] != '\0')
	{
		c = 0;
		while (ft_isdigit(params->line[i]))
		{
			rgb[c] = params->line[i];
			c++;
			i++;
		}
		if (params->line[i] == ',')
		{
			ft_cval(params, v, rgb, color);
			v++;
		}
		ft_val(params, color, v, rgb);
		i++;
	}
	return (v);
}

void	get_ciel_color(t_params *params)
{
	int		i;
	int		v;
	t_rgb	color;

	i = 0;
	v = 0;
	get_next_line(params->fd, &params->line);
	if (params->line[0] == 'C')
		v = ciel_values(params, &color, v);
	free(params->line);
	if (v < 2)
		returns("Error\n PLEASE FIX THE COLOR OF CIEL");
	params->ceil = rgb_to_hex(color.r, color.g, color.b);
}

void	get_floor_color(t_params *params)
{
	int		i;
	int		v;
	t_rgb	color;
	int		c;
	char	rgb[3];

	i = 0;
	v = 0;
	c = 0;
	get_next_line(params->fd, &params->line);
	if (params->line[0] == 'F')
		v = ciel_values(params, &color, v);
	free(params->line);
	if (v < 2)
		returns("Error\nPLEASE FIX THE COLOR OF FLOOR");
	params->floor = rgb_to_hex(color.r, color.g, color.b);
}
