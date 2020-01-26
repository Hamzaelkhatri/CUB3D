/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_seconde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:17:52 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 22:26:14 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	gnl(int fd, t_params *params)
{
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
	get_next_line(fd, &params->line);
}

void	press_rotleft(t_params *params)
{
	double olddirx;
	double oldplanex;

	olddirx = params->player->dir_x;
	oldplanex = params->player->plane_x;
	params->player->dir_x = params->player->dir_x *
		cos(params->player->rotate_speed) -
		params->player->dir_y *
		sin(params->player->rotate_speed);
	params->player->dir_y = olddirx * sin(params->player->rotate_speed) +
		params->player->dir_y *
		cos(params->player->rotate_speed);
	params->player->plane_x = params->player->plane_x *
		cos(params->player->rotate_speed) -
		params->player->plane_y *
		sin(params->player->rotate_speed);
	params->player->plane_y = oldplanex * sin(params->player->rotate_speed) +
		params->player->plane_y *
		cos(params->player->rotate_speed);
}

void	realse(t_params *params)
{
	mlx_clear_window(params->mlx, params->window);
	mlx_destroy_image(params->mlx, params->texx->img_ptr);
	params->texx->img_ptr = mlx_new_image(params->mlx,
			params->info->scren_with,
			params->info->scren_height);
	params->texx->data =
		(unsigned char *)mlx_get_data_addr(params->texx->img_ptr,
				&params->texx->bpp,
				&params->texx->size_line,
				&params->texx->endian);
	draw(params);
	mlx_put_image_to_window(params->mlx,
			params->window,
			params->texx->img_ptr, 0, 0);
}

int		res(int keycode, t_params *params)
{
	if (keycode == RIGHT)
		params->key.r = 0;
	else if (keycode == LEFT)
		params->key.l = 0;
	else if (keycode == ROTLEFT)
		params->key.rol = 0;
	else if (keycode == ROTRIGHT)
		params->key.ror = 0;
	else if (keycode == UP)
		params->key.u = 0;
	else if (keycode == DOWN)
		params->key.d = 0;
	else if (keycode == EXIT)
		params->key.e = 0;
	return (0);
}

int		presskey(int keycode, t_params *params)
{
	if (keycode == RIGHT)
		params->key.r = 1;
	else if (keycode == LEFT)
		params->key.l = 1;
	else if (keycode == ROTLEFT)
		params->key.rol = 1;
	else if (keycode == ROTRIGHT)
		params->key.ror = 1;
	else if (keycode == UP)
		params->key.u = 1;
	else if (keycode == DOWN)
		params->key.d = 1;
	else if (keycode == EXIT)
		params->key.e = 1;
	return (0);
}
