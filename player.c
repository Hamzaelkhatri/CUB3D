/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:05:14 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/17 00:36:40 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <stdio.h>
int presskey(int keycode, t_params *params)
{
    char **worldMap = params->world_map;

    if (keycode == RIGHT)
    {
	if (worldMap[(int)params->player->posy]
		[(int)(params->player->posx + params->player->plane_x
		* params->player->speed)] == '0')
		params->player->posx += params->player->plane_x
		* params->player->speed;
	if (worldMap[(int)(params->player->posy
		+ params->player->plane_y * params->player->speed)]
		[(int)params->player->posx] == '0')
		params->player->posy += params->player->plane_y
		* params->player->speed;
        write(1,"HEKKO",5);

        // mlx_clear_window(params->mlx, params->window);
        // mlx_destroy_image(params->mlx, params->img->img_mlx);
        // void *img_mlx = mlx_new_image(params->mlx, params->info->scren_with, params->info->scren_height);
        // params->img->img_mlx = img_mlx;
        // create_img(params->img, params->img->img_mlx, params);
        // draw_background(params);
        // draw(params);
        // mlx_put_image_to_window(params->mlx, params->window, img_mlx, 0, 0);
    }
    if (keycode == LEFT)
    {
	if (worldMap[(int)params->player->posy]
		[(int)(params->player->posx - params->player->plane_x
		* params->player->speed)] == '0')
		params->player->posx -= params->player->plane_x
		* params->player->speed;
	if (worldMap[(int)(params->player->posy
		- params->player->plane_y * params->player->speed)]
		[(int)params->player->posx] == '0')
		params->player->posy -= params->player->plane_y
		* params->player->speed;
    }
    if (keycode == DOWN)
    {
	if (worldMap[(int)params->player->posy]
		[(int)(params->player->posx - params->player->dir_x
		* params->player->speed)] == '0')
		params->player->posx -= params->player->dir_x
		* params->player->speed;
	if (worldMap[(int)(params->player->posy
		- params->player->dir_y * params->player->speed)]
		[(int)params->player->posx] == '0')
		params->player->posy -= params->player->dir_y
		* params->player->speed;
    }
    if (keycode == UP)
    {
   	if (worldMap[(int)params->player->posy]
		[(int)(params->player->posx + params->player->dir_x
		* params->player->speed)] == '0')
		params->player->posx += params->player->dir_x
		* params->player->speed;
	if (worldMap[(int)(params->player->posy
		+ params->player->dir_y * params->player->speed)]
		[(int)params->player->posx] == '0')
		params->player->posy += params->player->dir_y
		* params->player->speed;
    }
    if (keycode == EXIT)
    {
        mlx_destroy_window(params->mlx, params->window);
        exit(1);
    }
    if (keycode == ROTRIGHT)
    {
	double olddirx;
	double oldplanex;

	olddirx = params->player->dir_x;
	oldplanex = params->player->plane_x;
	params->player->dir_x = params->player->dir_x * cos(-params->player->rotate_speed) - params->player->dir_y* sin(-params->player->rotate_speed);
	params->player->dir_y = olddirx * sin(-params->player->rotate_speed)+ params->player->dir_y * cos(-params->player->rotate_speed);
	params->player->plane_x = params->player->plane_x * cos(-params->player->rotate_speed) - params->player->plane_y* sin(-params->player->rotate_speed);
	params->player->plane_y = oldplanex* sin(-params->player->rotate_speed) + params->player->plane_y* cos(-params->player->rotate_speed);
    }
    if (keycode == ROTLEFT)
    {
        double olddirx;
	    double oldplanex;
	    olddirx = params->player->dir_x;
	    oldplanex = params->player->plane_x;
	    params->player->dir_x = params->player->dir_x* cos(params->player->rotate_speed) - params->player->dir_y* sin(params->player->rotate_speed);
	    params->player->dir_y = olddirx * sin(params->player->rotate_speed)+ params->player->dir_y * cos(params->player->rotate_speed);
	    params->player->plane_x = params->player->plane_x* cos(params->player->rotate_speed) - params->player->plane_y* sin(params->player->rotate_speed);
	    params->player->plane_y = oldplanex* sin(params->player->rotate_speed) + params->player->plane_y* cos(params->player->rotate_speed);
    }
    if (keycode == RIGHT || keycode == LEFT || keycode == ROTLEFT || keycode == ROTRIGHT || keycode == UP || keycode == DOWN)
    {
        mlx_clear_window(params->mlx, params->window);
        mlx_destroy_image(params->mlx, params->texx->img_ptr);
        params->texx->img_ptr = mlx_new_image(params->mlx, params->info->scren_with, params->info->scren_height);
        params->texx->data = mlx_get_data_addr(params->texx->img_ptr, &params->texx->bpp,
                                               &params->texx->size_line, &params->texx->endian);
        raycasting(params);
        mlx_put_image_to_window(params->mlx, params->window, params->texx->img_ptr, 0, 0);
    }
    return (0);
}
