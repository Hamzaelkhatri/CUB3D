/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:11:40 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:29:24 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "unistd.h"

int		get_texture(t_params *params, char *path, int id)
{
	if (!(params->tex[id]->img_ptr =
			mlx_xpm_file_to_image(params->mlx, path,
			&params->tex[id]->width, &params->tex[id]->height)))
		returns("Error\n PLEASE CHECK THE TEXTURES");
	params->tex[id]->data =
		(unsigned char *)mlx_get_data_addr(params->tex[id]->img_ptr,
			&params->tex[id]->bpp,
			&params->tex[id]->size_line, &params->tex[id]->endian);
	return (0);
}

void	textures_path(t_position *pos, t_params *params)
{
	get_texture(params, params->path_no, pos->n);
	get_texture(params, params->path_so, pos->s);
	get_texture(params, params->path_we, pos->w);
	get_texture(params, params->path_es, pos->e);
}

void	nord(t_position *pos)
{
	pos->n = 0;
	pos->s = 1;
	pos->w = 2;
	pos->e = 3;
}

void	sud(t_position *pos)
{
	pos->n = 1;
	pos->s = 0;
	pos->w = 3;
	pos->e = 2;
}

void	texture_position(t_params *params)
{
	t_position *pos;

	if (!(pos = malloc(sizeof(t_position))))
		returns("Eror\n");
	if (params->position == 'N')
		nord(pos);
	else if (params->position == 'S')
		sud(pos);
	else if (params->position == 'W')
	{
		pos->n = 3;
		pos->s = 2;
		pos->w = 0;
		pos->e = 1;
	}
	else if (params->position == 'E')
	{
		pos->n = 2;
		pos->s = 3;
		pos->w = 1;
		pos->e = 0;
	}
	else
		returns("CHECK THE POSITION ");
	textures_path(pos, params);
}
