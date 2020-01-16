/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:05:14 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/16 00:08:55 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
int presskey(int keycode, t_params *params)
{
    int **worldMap = params->world_map;

    if (keycode == RIGHT)
    {
        if (worldMap[(int)(params->posY - params->dirX * 0.3)][(int)(params->posX)] == 0)
            params->posY += -params->dirX * 0.03;
        if (worldMap[(int)(params->posY)][(int)(params->posX + params->dirY * 0.3)] == 0)
            params->posX += params->dirY * 0.03;

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
        if (worldMap[(int)(params->posY + params->dirX * 0.3)][(int)(params->posX)] == 0)
            params->posY -= -params->dirX * 0.03;
        if (worldMap[(int)(params->posY)][(int)(params->posX - params->dirY * 0.3)] == 0)
            params->posX -= params->dirY * 0.03;
    }
    if (keycode == UP)
    {
        if (worldMap[(int)(params->posX + params->dirX * 0.3)][(int)(params->posY)] == 0)
            params->posX += params->dirX * 0.3;
        if (worldMap[(int)(params->posX)][(int)(params->posY + params->dirY * 0.3)] == 0)
            params->posY += params->dirY * 0.3;
    }
    if (keycode == DOWN)
    {
        if (worldMap[(int)(params->posX - params->dirX * 0.3)][(int)(params->posY)] == 0)
            params->posX -= params->dirX * 0.3;
        if (worldMap[(int)(params->posX)][(int)(params->posY - params->dirY * 0.3)] == 0)
            params->posY -= params->dirY * 0.3;
    }
    if (keycode == EXIT)
    {
        mlx_destroy_window(params->mlx, params->window);
        exit(1);
    }
    if (keycode == ROTRIGHT)
    {
        double oldDirX = params->dirX;
        params->dirX = params->dirX * cos(-0.1) - params->dirY * sin(-0.1);
        params->dirY = oldDirX * sin(-0.1) + params->dirY * cos(-0.1);
        double oldPlaneX = params->planeX;
        params->planeX = params->planeX * cos(-0.1) - params->planeY * sin(-0.1);
        params->planeY = oldPlaneX * sin(-0.1) + params->planeY * cos(-0.1);
    }
    if (keycode == ROTLEFT)
    {
        double oldDirX = params->dirX;
        params->dirX = params->dirX * cos(0.1) - params->dirY * sin(0.1);
        params->dirY = oldDirX * sin(0.1) + params->dirY * cos(0.1);
        double oldPlaneX = params->planeX;
        params->planeX = params->planeX * cos(0.1) - params->planeY * sin(0.1);
        params->planeY = oldPlaneX * sin(0.1) + params->planeY * cos(0.1);
    }
    if (keycode == RIGHT || keycode == LEFT || keycode == ROTLEFT || keycode == ROTRIGHT || keycode == UP || keycode == DOWN)
    {
        mlx_destroy_image(params->mlx, params->img->img_mlx);
        params->img->img_mlx = mlx_new_image(params->mlx, params->info->scren_with, params->info->scren_height);
        create_img(params->img, params->img->img_mlx, params);
        draw_background(params);
        draw(params);
        mlx_put_image_to_window(params->mlx, params->window, params->img->img_mlx, 0, 0);
    }
    return (0);
}
