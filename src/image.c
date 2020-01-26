/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 22:09:37 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	texture_on_img(t_point *line,
		t_tex *texture,
		t_params *params,
		t_ray *ray)
{
	int d;

	d = line->y * texture->size_line - params->info->scren_height
		* texture->size_line / 2 +
		ray->line_height * texture->size_line / 2;
	line->tex_y = ((d * texture->height) / ray->line_height) /
		texture->size_line;
	params->texx->data[line->y * params->texx->size_line +
		line->x * params->texx->bpp / 8] =
		texture->data[line->tex_y * texture->size_line +
		line->tex_x * (texture->bpp / 8)];
	params->texx->data[line->y * params->texx->size_line +
		line->x * params->texx->bpp / 8 + 1] = texture->data[line->tex_y *
		texture->size_line + line->tex_x * (texture->bpp / 8) + 1];
	params->texx->data[line->y * params->texx->size_line +
		line->x * params->texx->bpp / 8 + 2] =
		texture->data[line->tex_y * texture->size_line +
		line->tex_x * (texture->bpp / 8) + 2];
}
