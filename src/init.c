/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:36:11 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:29:57 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ini_image(t_params *params)
{
	if (!(params->texx->img_ptr =
				mlx_new_image(params->mlx,
					params->info->scren_with, params->info->scren_height)))
		returns("EREUR\n");
	params->texx->data =
		(unsigned char *)mlx_get_data_addr(params->texx->img_ptr,
				&params->texx->bpp, &params->texx->size_line,
				&params->texx->endian);
	params->texx->width = params->info->scren_with;
	params->texx->height = params->info->scren_height;
	return (0);
}

void	init_player(t_params *params)
{
	params->player->speed = 0.20;
	params->player->dir_x = -1;
	params->player->dir_y = 0;
	params->player->plane_x = 0;
	params->player->plane_y = 0.66;
	params->player->rotate_speed = 0.05;
}

void	init_key(t_params *params)
{
	params->key.l = 0;
	params->key.d = 0;
	params->key.u = 0;
	params->key.r = 0;
	params->key.rol = 0;
	params->key.ror = 0;
	params->key.e = 0;
}

void	init_tex_sprite(t_params *params)
{
	if (!(params->sprite = malloc(sizeof(t_tex))))
		returns("HELLO\n");
	ft_bzero(params->sprite, sizeof(t_tex));
	if (!(params->sprites = malloc(sizeof(t_list))))
		returns("HELLO\n");
	ft_bzero(params->sprites, sizeof(t_list));
	params->sprites->x = 1;
	params->sprites->y = 1;
	params->sprite->height = 0;
	params->sprite->width = 0;
	params->sprites->next = NULL;
}

int		ini_params(t_params *params)
{
	int count;

	count = 0;
	params->tex = malloc(sizeof(t_tex));
	(params->tex == NULL ? returns("\n") : 0);
	ft_bzero(params->tex, sizeof(t_tex));
	if (!(params->texx = malloc(sizeof(t_tex))))
		return (returns("EROR\n"));
	ft_bzero(params->texx, sizeof(t_tex));
	while (count < 4)
	{
		if (!(params->tex[count] = malloc(sizeof(t_tex))))
			return (-1);
		ft_bzero(params->tex[count], sizeof(t_tex));
		count++;
	}
	return (1);
}
