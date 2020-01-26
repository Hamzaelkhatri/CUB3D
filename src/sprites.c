/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:09:47 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:33:31 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calcul_values(t_draw_sprite *ds, t_params *params)
{
	ds->inv_det = 1 / (params->player->plane_x * params->player->dir_y
			- params->player->dir_x * params->player->plane_y);
	ds->transform_x = ds->inv_det * (params->player->dir_y * ds->sprite_x
			- params->player->dir_x * ds->sprite_y);
	ds->transform_y = ds->inv_det * (-params->player->plane_y
			* ds->sprite_x + params->player->plane_x * ds->sprite_y);
	ds->sprite_screen_x = (int)((params->info->scren_with / 2)
			* (1 + ds->transform_x / ds->transform_y));
	ds->sprite_height = abs((int)(params->info->scren_height
				/ ds->transform_y));
	ds->draw_start_y = -ds->sprite_height / 2
		+ ((params->info->scren_height / 2));
	if (ds->draw_start_y < 0)
		ds->draw_start_y = 0;
	ds->draw_end_y = ds->sprite_height / 2
		+ ((params->info->scren_height / 2));
	if (ds->draw_end_y >= params->info->scren_height)
		ds->draw_end_y = params->info->scren_height - 1;
	ds->sprite_width = abs((int)(params->info->scren_height
				/ ds->transform_y));
	ds->draw_start_x = -ds->sprite_width / 2 + ds->sprite_screen_x;
	ft_calc(ds, params);
}

void	pix_on_sprite_image(
		t_draw_sprite *ds,
		t_params *params)
{
	ds->d = ds->y * params->sprite->size_line
		- (params->info->scren_height)
		* (params->sprite->size_line / 2) + ds->sprite_height
		* params->sprite->size_line / 2;
	ds->tex_y = ((ds->d * params->sprite->height)
			/ ds->sprite_height) / params->sprite->size_line;
	ds->totcolor = params->sprite->data[ds->tex_y
		* params->sprite->size_line + ds->tex_x * params->sprite->bpp / R]
		+ params->sprite->data[ds->tex_y
		* params->sprite->size_line + ds->tex_x
		* params->sprite->bpp / R + 1] +
		params->sprite->data[ds->tex_y * params->sprite->size_line
		+ ds->tex_x * params->sprite->bpp / R + 2];
}

void	draw_spt(
		t_draw_sprite *ds,
		t_params *params)
{
	params->texx->data[ds->y * params->texx->size_line
		+ ds->stripe * params->texx->bpp / R] =
		params->sprite->data[ds->tex_y * params->sprite->size_line
		+ ds->tex_x * params->sprite->bpp / R];
	params->texx->data[ds->y * params->texx->size_line
		+ ds->stripe * params->texx->bpp / R + 1] =
		params->sprite->data[ds->tex_y * params->sprite->size_line
		+ ds->tex_x * params->sprite->bpp / R + 1];
	params->texx->data[ds->y * params->texx->size_line
		+ ds->stripe * params->texx->bpp / R + 2] =
		params->sprite->data[ds->tex_y * params->sprite->size_line
		+ ds->tex_x * params->sprite->bpp / R + 2];
}

void	make_sprite(
		t_draw_sprite *ds,
		t_params *params,
		t_ray *ray)
{
	ds->sprite_x = ds->sprites[ds->i].x - (params->player->posx) - 0.5;
	ds->sprite_y = ds->sprites[ds->i].y - (params->player->posy) - 0.5;
	calcul_values(ds, params);
	while (ds->stripe < ds->draw_end_x)
	{
		ds->tex_x = (int)(params->sprite->size_line * (ds->stripe
		- (-ds->sprite_width / 2 + ds->sprite_screen_x))
				* params->sprite->width / ds->sprite_width)
				/ params->sprite->size_line;
		if (ds->transform_y > 0 && ds->stripe > 0
				&& ds->stripe < params->info->scren_with
				&& ds->transform_y < ray->buffer[ds->stripe])
		{
			ds->y = ds->draw_start_y;
			while (ds->y < ds->draw_end_y)
			{
				pix_on_sprite_image(ds, params);
				if (ds->totcolor != 0)
					draw_spt(ds, params);
				ds->y++;
			}
		}
		ds->stripe++;
	}
}

int		draw_sprite(
		t_ray *ray,
		t_params *params)
{
	t_draw_sprite *ds;

	if (!(ds = malloc(sizeof(t_draw_sprite))))
		returns("problem in sprite");
	ft_bzero(ds, sizeof(t_draw_sprite));
	ds->i = 0;
	ds->sprites = list_to_tab(params);
	sort_sprite(params, ds->sprites,
			ft_lstsize((t_list *)params->sprites));
	while (ds->i < ft_lstsize((t_list *)params->sprites))
	{
		make_sprite(ds, params, ray);
		ds->i++;
	}
	return (1);
}
