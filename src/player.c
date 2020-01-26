/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:05:14 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	press_right(t_params *params)
{
	char **worldmap;

	worldmap = params->world_map;
	if (worldmap[(int)params->player->posy]
			[(int)(params->player->posx +
				params->player->plane_x * params->player->speed)] == '0')
		params->player->posx += params->player->plane_x *
			params->player->speed;
	if (worldmap[(int)(params->player->posy + params->player->plane_y *
				params->player->speed)]
			[(int)params->player->posx] == '0')
		params->player->posy += params->player->plane_y *
				params->player->speed;
}

void	press_left(t_params *params)
{
	char **worldmap;

	worldmap = params->world_map;
	if (worldmap[(int)params->player->posy]
			[(int)(params->player->posx -
				params->player->plane_x *
				params->player->speed)] == '0')
		params->player->posx -= params->player->plane_x * params->player->speed;
	if (worldmap[(int)(params->player->posy -
				params->player->plane_y * params->player->speed)]
			[(int)params->player->posx] == '0')
		params->player->posy -= params->player->plane_y * params->player->speed;
}

void	press_down(t_params *params)
{
	char **worldmap;

	worldmap = params->world_map;
	if (worldmap[(int)params->player->posy]
			[(int)(params->player->posx -
				params->player->dir_x *
				params->player->speed)] == '0')
		params->player->posx -= params->player->dir_x * params->player->speed;
	if (worldmap[(int)(params->player->posy -
				params->player->dir_y * params->player->speed)]
			[(int)params->player->posx] == '0')
		params->player->posy -= params->player->dir_y * params->player->speed;
}

void	press_up(t_params *params)
{
	char **worldmap;

	worldmap = params->world_map;
	if (worldmap[(int)params->player->posy]
			[(int)(params->player->posx +
				params->player->dir_x *
				params->player->speed)] == '0')
		params->player->posx += params->player->dir_x *
			params->player->speed;
	if (worldmap[(int)(params->player->posy +
				params->player->dir_y *
				params->player->speed)]
			[(int)params->player->posx] == '0')
		params->player->posy += params->player->dir_y *
				params->player->speed;
}

void	press_rotright(t_params *params)
{
	double olddirx;
	double oldplanex;

	olddirx = params->player->dir_x;
	oldplanex = params->player->plane_x;
	params->player->dir_x = params->player->dir_x *
		cos(-params->player->rotate_speed) -
		params->player->dir_y *
		sin(-params->player->rotate_speed);
	params->player->dir_y = olddirx *
		sin(-params->player->rotate_speed) +
		params->player->dir_y *
		cos(-params->player->rotate_speed);
	params->player->plane_x = params->player->plane_x *
		cos(-params->player->rotate_speed) -
		params->player->plane_y *
		sin(-params->player->rotate_speed);
	params->player->plane_y = oldplanex *
		sin(-params->player->rotate_speed) +
		params->player->plane_y *
		cos(-params->player->rotate_speed);
}
