/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 06:08:18 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 23:00:13 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_texture(t_point *line,
		t_params *params,
		t_tex *texture,
		t_ray *ray)
{
	int y_max;

	if (line->y0 < line->y1)
	{
		line->y = line->y0;
		y_max = line->y1;
	}
	else
	{
		line->y = line->y1;
		y_max = line->y0;
	}
	if (line->y >= 0)
	{
		while (line->y < y_max)
		{
			texture_on_img(line, texture, params, ray);
			line->y++;
		}
	}
}

void	get_side(
		t_ray *ray,
		t_params *params,
		t_point *line,
		double wall_x)
{
	t_tex	*texx;
	int		tex_x;

	if (ray->side == 0)
		texx = params->tex[1];
	if (ray->side == 1)
		texx = params->tex[0];
	if (ray->side == 2)
		texx = params->tex[2];
	if (ray->side == 3)
		texx = params->tex[3];
	tex_x = (int)(wall_x * (double)texx->width);
	if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
		tex_x = texx->width - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
		tex_x = texx->width - tex_x - 1;
	line->y0 = ray->draw_end;
	line->y1 = ray->draw_start;
	line->tex_x = tex_x;
	draw_texture(line, params, texx, ray);
}

void	pixel_put_to_image(int color, int x,
		int y,
		t_params *params)
{
	unsigned char	*src;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				k;

	k = (int)((y) * params->texx->size_line + (x) * 4);
	src = (unsigned char *)&color;
	r = src[0];
	g = src[1];
	b = src[2];
	params->texx->data[y * params->texx->size_line +
		x * params->texx->bpp / 8] = r;
	params->texx->data[y * params->texx->size_line +
		x * params->texx->bpp / 8 + 1] = g;
	params->texx->data[y * params->texx->size_line +
		x * params->texx->bpp / 8 + 2] = b;
}

void	draw_color(t_point *line, t_params *params,
		int color)
{
	int y;
	int y_max;

	if (line->y0 < line->y1)
	{
		y = line->y0;
		y_max = line->y1;
	}
	else
	{
		y = line->y1;
		y_max = line->y0;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			pixel_put_to_image(color, line->x, y, params);
			y++;
		}
	}
}

void	set_texture(t_ray *ray, t_params *params)
{
	t_tex		*img;
	t_point		*line;
	double		wall_x;

	if (!(line = malloc(sizeof(t_point))))
		returns("\n");
	ft_bzero(line, sizeof(t_point));
	line->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = params->player->posy + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = params->player->posx + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (params->world_map[ray->mapy][ray->mapx] == '1')
		get_side(ray, params, line, wall_x);
	line->y = 0;
	line->y0 = 0;
	line->y1 = ray->draw_start;
	draw_color(line, params, params->ceil);
	line->y0 = params->info->scren_height;
	line->y1 = ray->draw_end;
	draw_color(line, params, params->floor);
}
