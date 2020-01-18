/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 06:08:18 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/17 08:45:16 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void texture_on_img(t_point *line, t_tex *texture, t_params *win_infos, t_ray *ray)
{
    int d;

    d = line->y * texture->size_line - win_infos->info->scren_height * texture->size_line / 2 + ray->line_height * texture->size_line / 2;
    line->tex_y = ((d * texture->height) / ray->line_height) / texture->size_line;
    win_infos->texx->data[line->y * win_infos->texx->size_line + line->x * win_infos->texx->bpp / 8] = texture->data[line->tex_y * texture->size_line + line->tex_x * (texture->bpp / 8)];
    win_infos->texx->data[line->y * win_infos->texx->size_line + line->x * win_infos->texx->bpp / 8 + 1] = texture->data[line->tex_y * texture->size_line + line->tex_x * (texture->bpp / 8) + 1];
    win_infos->texx->data[line->y * win_infos->texx->size_line + line->x * win_infos->texx->bpp / 8 + 2] = texture->data[line->tex_y * texture->size_line + line->tex_x * (texture->bpp / 8) + 2];
}

void draw_texture(t_point *line, t_params *win_infos, t_tex *texture, t_ray *ray)
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
            texture_on_img(line, texture, win_infos, ray);
            line->y++;
        }
    }
}

static void determine_side_draw(
    t_ray *ray,
    t_params *win_infos,
    t_point *line,
    double wall_x)
{
    t_tex *texx;
    int tex_x;

    if (ray->side == 0)
        texx = win_infos->tex[1];
    if (ray->side == 1)
        texx = win_infos->tex[0];
    if (ray->side == 2)
        texx = win_infos->tex[2];
    if (ray->side == 3)
        texx = win_infos->tex[3];
    tex_x = (int)(wall_x * (double)texx->width);
    if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
        tex_x = texx->width - tex_x - 1;
    if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
        tex_x = texx->width - tex_x - 1;
    line->y0 = ray->draw_end;
    line->y1 = ray->draw_start;
    line->tex_x = tex_x;
    draw_texture(line, win_infos, texx, ray);
}

void pixel_put_to_image(int color, int x, int y, t_params *win_infos)
{
    unsigned char *src;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int k;
    k = (int)((y)*win_infos->texx->size_line + (x)*4);
    src = (unsigned char *)&color;
    r = src[0];
    g = src[1];
    b = src[2];
    win_infos->texx->data[y * win_infos->texx->size_line + x * win_infos->texx->bpp / 8] = r;
    win_infos->texx->data[y * win_infos->texx->size_line + x * win_infos->texx->bpp / 8 + 1] = g;
    win_infos->texx->data[y * win_infos->texx->size_line + x * win_infos->texx->bpp / 8 + 2] = b;
}

void draw_color(t_point *line, t_params *win_infos,
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
            pixel_put_to_image(color, line->x, y, win_infos);
            y++;
        }
    }
}

void set_texture(t_ray *ray, t_params *win_infos)
{
    t_tex *img;
    t_point *line;
    double wall_x;

    if (!(line = malloc(sizeof(t_point))))
        return ((void)0);
    ft_bzero(line, sizeof(t_point));
    line->x = ray->pix;
    if (ray->side == 0 || ray->side == 1)
        wall_x = win_infos->player->posy + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = win_infos->player->posx + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x -= floor(wall_x);
    if (win_infos->world_map[ray->mapy][ray->mapx] == '1')
        determine_side_draw(ray, win_infos, line, wall_x);
    line->y = 0;
    line->y0 = 0;
    line->y1 = ray->draw_start;
    win_infos->color_ceiling = 0x82c8f7;
    draw_color(line, win_infos, win_infos->color_ceiling);
    line->y0 = win_infos->info->scren_height;
    line->y1 = ray->draw_end;
    win_infos->color_floor = 0x707270;
    draw_color(line, win_infos, win_infos->color_floor);
}

void perp_and_height(t_ray *ray, t_player *player, t_params *win_infos)
{
    if (ray->side == 0 || ray->side == 1)
        ray->perp_wall_dist = (ray->mapx - player->posx + (1 - ray->step_x) / 2) / ray->ray_dir_x; //(mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
    else
        ray->perp_wall_dist = (ray->mapy - player->posy + (1 - ray->step_y) / 2) / ray->ray_dir_y;
    ray->line_height = (int)(win_infos->info->scren_height / ray->perp_wall_dist);
    if (ray->perp_wall_dist == 0)
        ray->line_height = 1000;
    ray->draw_start = -ray->line_height / 2 + win_infos->info->scren_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + win_infos->info->scren_height / 2;
    if (ray->draw_end >= win_infos->info->scren_height)
        ray->draw_end = win_infos->info->scren_height - 1;
}

void get_sides(t_ray *ray)
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

void hit(t_ray *ray, t_params *win_infos)
{
    while (ray->hit == 0)
    {
        get_sides(ray);
        if (win_infos->world_map[ray->mapy][ray->mapx] > '0' && win_infos->world_map[ray->mapy][ray->mapx] != '2')
            ray->hit = 1;
        // else if (win_infos->map->map[ray->mapy][ray->mapx] == '2')
        // 	is_sprite(ray, win_infos);
    }
}

static void steps(t_ray *ray, t_player *player)
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

static void init_ray(t_ray *ray, t_player *player, t_params *win_infos)
{
    ray->camera_x = (2 * ray->pix) / (double)win_infos->info->scren_with - 1;
    ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
    ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
    ray->mapx = (int)player->posx;
    ray->mapy = (int)player->posy;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
}

static void raycasting_tw(t_params *win_infos, t_ray *ray)
{
    t_player *player;

    player = win_infos->player;
    init_ray(ray, player, win_infos);
    steps(ray, player);
    hit(ray, win_infos);
    perp_and_height(ray, player, win_infos);
    set_texture(ray, win_infos);
    ray->pix++;
}

int raycasting(t_params *win_infos)
{
    t_ray *ray;

    if (!(ray = malloc(sizeof(t_ray))))
        return (-1);
    ft_bzero(ray, sizeof(t_ray));
    if (!(ray->z_buffer = malloc(sizeof(double) * win_infos->info->scren_with)))
        return (-1);
    ft_bzero(ray->z_buffer, sizeof(double) * win_infos->info->scren_with);
    while (ray->pix < win_infos->info->scren_with)
        raycasting_tw(win_infos, ray);
    mlx_put_image_to_window(win_infos->mlx, win_infos->window, win_infos->texx->img_ptr, 0, 0);
    return (1);
}