/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 22:07:48 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:24:07 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		draw(t_params *params)
{
	t_ray *ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (-1);
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->buffer = malloc(sizeof(double) *
					params->info->scren_with)))
		return (-1);
	ft_bzero(ray->buffer, sizeof(double) *
			params->info->scren_with);
	while (ray->pix < params->info->scren_with)
		raycasting_tw(params, ray);
	if (!draw_sprite(ray, params))
		returns("EROR\n PROBLEM IN SPRITE");
	mlx_put_image_to_window(params->mlx, params->window,
			params->texx->img_ptr, 0, 0);
	free(ray->buffer);
	free(ray);
	return (1);
}

void	get_sides(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->mapx += ray->step_x;
		if (ray->step_x == 1)
			ray->side = 0;
		else if (ray->step_x < 0)
			ray->side = 1;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->mapy += ray->step_y;
		if (ray->step_y == 1)
			ray->side = 2;
		else if (ray->step_y < 0)
			ray->side = 3;
	}
}

int		set_sprite(char *path, t_params *params)
{
	params->sprite->img_ptr =
		mlx_xpm_file_to_image(params->mlx, path,
				&params->sprite->width,
				&params->sprite->height);
	params->sprite->bpp = 0;
	params->sprite->size_line = 0;
	params->sprite->endian = 0;
	if (!params->sprite->img_ptr)
		returns("error \n check path of sprite");
	params->sprite->data =
		(unsigned char *)mlx_get_data_addr(params->sprite->img_ptr,
				&params->sprite->bpp,
				&params->sprite->size_line,
				&params->sprite->endian);
	if (params->sprite->data <= 0)
		exit(0);
	return (1);
}

void	next_sprite(
		t_sprites *actual,
		t_sprites *new,
		t_ray *ray)
{
	while (1)
	{
		if (actual->x == ray->mapx && actual->y == ray->mapy)
		{
			free(new);
			break ;
		}
		if ((actual->x != ray->mapx || actual->y != ray->mapy) && !actual->next)
		{
			actual->next = new;
			break ;
		}
		if (actual->next != NULL)
			actual = actual->next;
		else
		{
			free(new);
			break ;
		}
	}
}

void	perp_and_height(t_ray *ray, t_player *player, t_params *params)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist =
		(ray->mapx - player->posx
		+ (1 - ray->step_x) / 2)
		/ ray->ray_dir_x;
	else
		ray->perp_wall_dist =
			(ray->mapy - player->posy
		+ (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->line_height =
		(int)(params->info->scren_height
				/ ray->perp_wall_dist);
	if (ray->line_height == 0)
		ray->line_height = 1000;
	ray->draw_start = -ray->line_height
		/ 2 + params->info->scren_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height
		/ 2 + params->info->scren_height / 2;
	if (ray->draw_end >= params->info->scren_height)
		ray->draw_end = params->info->scren_height - 2;
}
