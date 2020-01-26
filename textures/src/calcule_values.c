/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcule_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 22:06:27 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 00:00:15 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	hit(t_ray *ray, t_params *params)
{
	while (ray->hit == 0)
	{
		get_sides(ray);
		if (params->world_map[ray->mapy][ray->mapx] != '0' &&
				params->world_map[ray->mapy][ray->mapx] != '2')
			ray->hit = 1;
		else if (params->world_map[ray->mapy][ray->mapx] == '2')
			is_sprite(ray, params);
	}
}

void	steps(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->posx - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->mapx + 1.0 - player->posx) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->posy - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->mapy + 1.0 - player->posy) * ray->delta_dist_y;
	}
}

void	init_ray(t_ray *ray, t_player *player, t_params *params)
{
	ray->camera_x = (2 * ray->pix) / (double)params->info->scren_with - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->mapx = (int)player->posx;
	ray->mapy = (int)player->posy;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	raycasting_tw(t_params *params, t_ray *ray)
{
	t_player *player;

	player = params->player;
	init_ray(ray, player, params);
	steps(ray, player);
	hit(ray, params);
	perp_and_height(ray, player, params);
	ray->buffer[ray->pix] = ray->perp_wall_dist;
	set_texture(ray, params);
	ray->pix++;
}

void	hud_tex(t_params *params)
{
	mlx_string_put(params->mlx,
			params->window, 10, 10, 0xfffffff, "ECS : CLOSE");
	mlx_string_put(params->mlx,
			params->window, 10, 30, 0xfffffff, "W : UP");
	mlx_string_put(params->mlx,
			params->window, 10, 50, 0xfffffff, "A : LEFT");
	mlx_string_put(params->mlx,
			params->window, 10, 70, 0xfffffff, "D : RIGHT");
	mlx_string_put(params->mlx,
			params->window, 10, 90, 0xfffffff, "S : DOWN");
	mlx_string_put(params->mlx,
			params->window, 10, 120, 0xfffffff, "LEFT : ROTATION");
	mlx_string_put(params->mlx,
			params->window, 10, 140, 0xfffffff, "RIGHT : ROTATION");
}
