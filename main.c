/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:40 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/16 01:31:52 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void *ft_memcpy(void *dest, void const *scr, size_t n)
{
    int i;
    char *destmp;
    const unsigned char *srctmp;

    destmp = dest;
    srctmp = scr;
    i = 0;
    if (dest == NULL && scr == NULL)
    {
        return (NULL);
    }
    while (0 < n)
    {
        destmp[i] = srctmp[i];
        n--;
        i++;
    }
    return (destmp);
}

int ft_to_int(char c)
{
    return (c - 48);
}

// void pixel_put_to_image(
//     int color,
//     int x,
//     int y,
//     t_params *params)
// {
//     unsigned char *src;
//     unsigned char r;
//     unsigned char g;
//     unsigned char b;

//     src = (unsigned char *)&color;
//     r = src[0];
//     g = src[1];
//     b = src[2];
//     params->tex.cast[y * params->tex.sizeline + x * params->tex.bpp / 8] = r;
//     params->tex.cast[y * params->tex.sizeline + x * params->tex.bpp / 8 + 1] = g;
//     params->tex.cast[y * params->tex.sizeline + x * params->tex.bpp / 8 + 2] = b;
// }

static int operation(const char *str, int i, int l, int sign)
{
    int r;

    r = 0;
    while (str[i] != '\0' && str[i] <= 57 && str[i] >= 48)
    {
        r = r * 10 + str[i] - '0';
        i++;
        l++;
    }
    if (l > 19)
    {
        if (sign == 1)
            return (-1);
        else
            return (0);
    }
    return (sign * r);
}

// void ver_line_color_image(
//     t_vline *line,
//     t_params *params,
//     int color)
// {
//     int y;
//     int y_max;

//     if (line->start < line->end)
//     {
//         y = line->start;
//         y_max = line->end;
//     }
//     else
//     {
//         y = line->start;
//         y_max = line->end;
//     }
//     if (y >= 0)
//     {
//         while (y < y_max)
//         {
//             pixel_put_to_image(color, line->x, y, params);
//             y++;
//         }
//     }
// }

// void texturisation(t_params *params)
// {
//     t_vline *line;
//     double wall_x;

//     if (params->side == 0 || params->side == 1)
//         wall_x = params->posY + params->perp_wall_dist * params->dirY;
//     else
//         wall_x = params->posX + params->perp_wall_dist * params->posX;
//     wall_x -= floor(wall_x);
//     // if (params->world_map[params->info->mapheight][params->info->mapwidth] == '1')
//     //     determine_side_draw(line, params, wall_x);
//     // line->y = 0;
//     // line->y1 = line->start;
//     ver_line_color_image(line, params, params->color);
//     // line->y0 = win_infos->height;
//     // line->y1 = ray->draw_end;
//     ver_line_color_image(line, params, params->color);
// }

int ft_atoi(const char *str)
{
    size_t i;
    int sign;
    int l;

    i = 0;
    sign = 1;
    l = 0;
    while (str[i] == '\n' || str[i] == '\v' || str[i] == '\t' ||
           str[i] == '\r' || str[i] == ' ' || str[i] == '\f')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    return (operation(str, i, l, sign));
}

int ft_Width_map(char *str)
{
    int i;
    int len;
    i = 0;
    len = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '1' || str[i] == '0')
            len++;
        i++;
    }
    return (len);
}

void ft_putnb(int n)
{
    long long nb;

    nb = n;
    if (n < 0)
    {
        putchar('-');
        nb *= (-1);
    }
    if (nb >= 10)
    {
        ft_putnb(nb / 10);
        ft_putnb(nb % 10);
    }
    else
    {
        putchar(nb + '0');
    }
}

int ft_Height(t_params *parms)
{
    char *line;
    int fd;
    fd = open("map.cub", O_RDONLY);
    while (get_next_line(fd, &line))
    {
        parms->info->mapheight++;
        parms->info->mapwidth = ft_Width_map(line);
    }
    return (0);
}

int draw(t_params *params);
int ft_strchrr(char *str, int c)
{
    int i = 0;
    if (str[i] != '\0')
    {
        if (str[i] == c)
        {
            return (1);
        }
        i++;
    }
    return (0);
}

// void put_pxl_to_img(t_params *t, int x, int y, int color)
// {

//     if (x < t->info->scren_with && y < t->info->scren_height)
//     {
//         //(y * 2 - h + hauteurLigne)* (texHeight/2)/hauteurLigne
//         t->y_text = 10;
//         ft_memcpy(t->img_ptr + 4 * t->info->scren_with * y + x * 4, &t->tex[t->id].cast[t->y_text % 64 * t->tex[t->id].sizeline + t->x_text % 64 * t->tex[t->id].bpp / 8], sizeof(int));
//     }
//     // else if (x < t->info->scren_with && y < t->info->scren_height)
//     //  ft_memcpy(t->img_ptr + 4 * t->info->scren_with * y + x * 4,
//     //       &color, sizeof(int));
// }

// void draw_wall(int x, int start, int end, t_params *t, int rayPosX, int rayPosY, int perpWallDist)
// {
//     double X_wall;
//     t->id = 1;
//     if (t->side == 1)
//         X_wall = rayPosY + perpWallDist * rayPosY;
//     X_wall -= floor((X_wall));
//     t->x_text = (int)(X_wall * (double)(64));
//     if (t->side == 0 && rayPosX > 0)
//         t->x_text = 64 - t->x_text - 1;
//     if (t->side == 1 && rayPosX < 0)
//         t->x_text = 64 - t->x_text - 1;
//     //t->x_text = abs(t->x_text);
//     ft_putnb(t->color);
//     while (++start <= end)
//         put_pxl_to_img(t, x, start, t->color);
// }

size_t ft_strlen_w(const char *str)
{
    size_t i;
    int len;

    len = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '0' || str[i] == '1')
            len++;
        i++;
    }
    return (len);
}

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

void get_Height(char *str, int *h)
{
    int j;
    int i;
    char tab2[24];
    j = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]))
        {
            tab2[j] = str[i];
            j++;
        }
        i++;
    }
    tab2[j] = '\0';
    *h = ft_atoi(tab2);
}

void get_maphe(int fd, char *line, int *maphe, int *mapwe)
{
    int len;
    len = 0;
    get_next_line(fd, &line);
    while (get_next_line(fd, &line))
    {
        *mapwe = ft_strlen_w(line);
        len++;
    }
    *maphe = len;
}

void get_Resolution(t_params *params)
{
    int fd;
    int w;
    char *line;
    int i;
    int mapw;
    int maph;
    int o = 0;
    char tab[24];
    int j = 0;
    i = 0;
    fd = open("map.cub", O_RDONLY);
    get_next_line(fd, &line);

    while (line[i] != '\0')
    {
        if (ft_isdigit(line[i]))
        {
            tab[j] = line[i];
            (line[i + 1] == ' ' ? o = 1 : 0);
            j++;
        }
        i++;
        if (o == 1)
            break;
    }
    tab[j] = '\0';
    params->info->scren_with = ft_atoi(tab);
    get_Height(line + i, &w);
    params->info->scren_height = w;
    get_maphe(fd, line, &mapw, &maph);
    params->info->mapwidth = maph;
    params->info->mapheight = mapw;
}

void draw_floor(t_params *params)
{
    int i;
    t_point *p;

    p = (t_point *)malloc(sizeof(t_point));
    i = params->info->scren_height / 2;
    int y = 0;
    while (i < params->info->scren_height)
    {
        y = 0;
        while (y < params->info->scren_with)
        {
            p->x = y;
            p->y = i;
            p->colour = 0x707270;
            put_pixel_to_image(p, params->img);
            y++;
        }
        i++;
    }
}

void draw_ciel(t_params *params)
{
    int i;
    t_point *p;

    p = (t_point *)malloc(sizeof(t_point));
    i = 0;
    int y = 0;
    while (i < params->info->scren_height)
    {
        y = 0;
        while (y < params->info->scren_with)
        {
            p->x = y;
            p->y = i;
            p->colour = 0x82c8f7;
            put_pixel_to_image(p, params->img);
            y++;
        }
        i++;
    }
}

void get_map(t_params *pParams)
{
    int i = 0;
    int y = 0;
    int j;

    pParams->world_map = (int **)malloc(sizeof(int *) * pParams->info->mapheight + 1);
    get_next_line(pParams->fd, &pParams->line);
    get_next_line(pParams->fd, &pParams->line);
    printf("\n");
    while (i < pParams->info->mapheight && get_next_line(pParams->fd, &pParams->line))
    {
        pParams->world_map[i] = (int *)malloc(sizeof(int) * pParams->info->mapwidth + 1);
        j = 0;
        y = 0;

        while (y <= (int)pParams->info->mapwidth - 1 && pParams->line[j])
        {
            if ((pParams->line[j] == '0' || pParams->line[j] == '1'))
            {
                pParams->world_map[i][y] = ft_to_int(pParams->line[j]);
                printf("{%i}", pParams->world_map[i][y]);
                y++;
            }
            j++;
        }
        printf("\n");
        i++;
    }
}
void draw_background(t_params *params)
{
    draw_ciel(params);
    draw_floor(params);
}

// int ft_xpm(t_params *s, unsigned int **adr, char *file)
// {
//     int fd;
//     void *img;
//     int tab[5];

//     tab[0] = 100;
//     tab[1] = 100;
//     if ((fd = open(file, O_RDONLY)) == -1)
//         return (-1);
//     close(fd);
//     img = mlx_xpm_file_to_image(s->mlx, file, &tab[0], &tab[1]);
//     *adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
//     free(img);
//     return (0);
// }

// unsigned int ft_pixel(t_params *s, double i)
// {
//     int index;

//     if (floor(s->posY) == s->posY)
//     {
//         index = 64 * floor(64 * i) + 64 * (s->posX - floor(s->posX));
//         // if (s->w == 1)
//         //     return (s->tex.s[index]);
//         // else if (s->w == 0)
//         return (s->cast[index]);
//     }
//     else if (floor(s->posX) == s->posX)
//     {
//         index = 64 * floor(64 * i) + 64 * (s->posY - floor(s->posY));
//         // if (s->v == 1)
//         //     return (s->tex.e[index]);
//         // else if (s->v == 0)
//         return (s->tex.w[index]);
//     }
//     return (0x00000000);
// }

// void ft_column(t_params *s, int size)
// {
//     unsigned int color;
//     int start;
//     int count;

//     start = s->posX * (s->posY - size) / 2;
//     if (size > s->posY)
//         count = (size - s->posY) / 2;
//     else
//         count = 0;
//     color = s->tex.c;
//     int i = 0;
//     while (i < s->posX * s->posY)
//     {
//         if (i >= start && count < size)
//         {
//             color = ft_pixel(s, (double)count / size);
//             count++;
//         }
//         else if (count == size)
//             color = s->tex.f;
//         s->imgs.adr[i] = mlx_get_color_value(s->mlx, color);
//         i += s->posX;
//     }
//     i -= s->posX * s->posY;
// }

int ft_texturing(t_params *stock)
{
    int i;
    char path1[10] = "mossy.xpm";
    char path2[10] = "blue.xpm";
    char path3[10] = "hit.xpm";
    char path4[10] = "egle.xpm";
    int tab[50];
    int a = 64;
    int b = 64;

    // i = -1;
    // if (!(stock->tex.mlx_wall = malloc(sizeof(int *) * 4)) ||
    //     !(stock->tex.cast = malloc(sizeof(int *) * 4)))
    //     return (0);
    //stock->tex.mlx_wall = mlx_xpm_file_to_image(stock->mlx, path1, &a, &b);
    //stock->tex.cast = mlx_get_data_addr(stock->tex.mlx_wall, &stock->tex.bpp, &stock->tex.sizeline, &stock->tex.endian);
    // stock->tex[1].mlx_wall = mlx_xpm_file_to_image(stock->mlx, path2, &tab[4], &tab[5]);
    // stock->tex[1].cast = mlx_get_data_addr(stock->tex[1].mlx_wall, &stock->tex[0].bpp, &stock->tex[1].sizeline, &stock->tex[1].endian);
    // stock->tex[2].mlx_wall = mlx_xpm_file_to_image(stock->mlx, path2, &tab[9], &tab[10]);
    // stock->tex[2].cast = mlx_get_data_addr(stock->tex[2].mlx_wall, &stock->tex[0].bpp, &stock->tex[2].sizeline, &stock->tex[2].endian);
    // stock->tex[3].mlx_wall = mlx_xpm_file_to_image(stock->mlx, path2, &tab[14], &tab[15]);
    // stock->tex[3].cast = mlx_get_data_addr(stock->tex[3].mlx_wall, &stock->tex[0].bpp, &stock->tex[3].sizeline, &stock->tex[3].endian);
    return (1);
}

void *ft_memset(void *b, int c, size_t len)
{
    size_t i;
    unsigned char *buc;

    i = 0;
    buc = (unsigned char *)b;
    while (i < len)
    {
        buc[i] = c;
        i++;
    }
    return (b = buc);
}

void ft_bzero(void *str, size_t n)
{
    ft_memset(str, 0, n);
}

// static void do_raycasting(
// 	t_params *win_infos,
// 	t_ray *ray)
// {
// 	t_player *player;

// 	player = win_infos->player;
// 	init_values(ray, player, win_infos);
// 	next_step(ray, player);
// 	hit(ray, win_infos);
// 	perp_and_height(ray, player, win_infos);
// 	ray->z_buffer[ray->pix] = ray->perp_wall_dist;
// 	texturisation(ray, win_infos);
// 	ray->pix++;
// }

// int raycasting(
// 	t_params *win_infos)
// {
// 	t_ray *ray;

// 	if (!(ray = malloc(sizeof(t_ray))))
// 		return (-1);
// 	ft_bzero(ray, sizeof(t_ray));
// 	if (!(ray->z_buffer = malloc(sizeof(double) * win_infos->info->scren_with)))
// 		return (-1);
// 	ft_bzero(ray->z_buffer, sizeof(double) * win_infos->info->scren_with);
// 	while (ray->pix < win_infos->info->scren_with)
// 		do_raycasting(win_infos, ray);
// 	if (!draw_sprite(ray, win_infos))
// 		return (-1);
//     mlx_put_image_to_window(win_infos->mlx, win_infos->window,win_infos->img_ptr, 0, 0);
// 	return (-1);
// }

static void texture_on_img(
    t_point *line,
    t_tex *texture,
    t_params *win_infos,
    t_ray *ray)
{
    int d;

    d = line->y * texture->size_line - win_infos->info->scren_height * texture->size_line / 2 + ray->line_height * texture->size_line / 2;
    line->tex_y = ((d * texture->height) / ray->line_height) / texture->size_line;
    win_infos->texx->data[line->y * win_infos->texx->size_line + line->x * win_infos->texx->bpp / 8] = texture->data[line->tex_y * texture->size_line + line->tex_x * (texture->bpp / 8)];
    win_infos->texx->data[line->y * win_infos->texx->size_line + line->x * win_infos->texx->bpp / 8 + 1] = texture->data[line->tex_y * texture->size_line + line->tex_x * (texture->bpp / 8) + 1];
    win_infos->texx->data[line->y * win_infos->texx->size_line + line->x * win_infos->texx->bpp / 8 + 2] = texture->data[line->tex_y * texture->size_line + line->tex_x * (texture->bpp / 8) + 2];
}

void ver_line_texture_image(
    t_point *line,
    t_params *win_infos,
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

    texx = win_infos->tex[0];
    if (ray->side == 1)
        texx = win_infos->tex[0];
    if (ray->side == 2)
        texx = win_infos->tex[0];
    if (ray->side == 3)
        texx = win_infos->tex[0];
    tex_x = (int)(wall_x * (double)texx->width);
    if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
        tex_x = texx->width - tex_x - 1;
    if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
        tex_x = texx->width - tex_x - 1;
    line->y0 = ray->draw_end;
    line->y1 = ray->draw_start;
    line->tex_x = tex_x;
    ver_line_texture_image(line, win_infos, texx, ray);
}

void texturisation(
    t_ray *ray,
    t_params *win_infos)
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
    line->y0 = 0;
    line->y1 = ray->draw_start;
    //ver_line_color_image(line, win_infos, win_infos->color_ceiling);
    line->y0 = win_infos->info->scren_height;
    line->y1 = ray->draw_end;
    //ver_line_color_image(line, win_infos, win_infos->color_floor);
}

void perp_and_height(
    t_ray *ray,
    t_player *player,
    t_params *win_infos)
{
    if (ray->side == 0 || ray->side == 1)
        ray->perp_wall_dist = (ray->mapx - player->posx + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->mapy - player->posy + (1 - ray->step_y) / 2) / ray->ray_dir_y;
    ray->line_height = (int)(win_infos->info->scren_height / ray->perp_wall_dist);
    ray->draw_start = -ray->line_height / 2 + win_infos->info->scren_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + win_infos->info->scren_height / 2;
    if (ray->draw_end >= win_infos->info->scren_height)
        ray->draw_end = win_infos->info->scren_height - 1;
}

void predict_wall_face(
    t_ray *ray)
{
    if (ray->side_dist_x < ray->side_dist_y)
    {
        ray->side_dist_x += ray->delta_dist_x;
        ray->mapx += ray->step_x;
        if (ray->step_x == 1)
            ray->side = 0;
        else if (ray->step_x == -1)
            ray->side = 1;
    }
    else
    {
        ray->side_dist_y += ray->delta_dist_y;
        ray->mapy += ray->step_y;
        if (ray->step_y == 1)
            ray->side = 2;
        else if (ray->step_y == -1)
            ray->side = 3;
    }
}

void hit(
    t_ray *ray,
    t_params *win_infos)
{
    while (ray->hit == 0)
    {
        predict_wall_face(ray);
        if (win_infos->world_map[ray->mapy][ray->mapx] > '0' && win_infos->world_map[ray->mapy][ray->mapx] != '2')
            ray->hit = 1;
        // else if (win_infos->map->map[ray->mapy][ray->mapx] == '2')
        // 	is_sprite(ray, win_infos);
    }
}

static void next_step(
    t_ray *ray,
    t_player *player)
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

static void init_values(
    t_ray *ray,
    t_player *player,
    t_params *win_infos)
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

static void do_raycasting(
    t_params *win_infos,
    t_ray *ray)
{
    t_player *player;

    player = win_infos->player;
    init_values(ray, player, win_infos);
    next_step(ray, player);
    hit(ray, win_infos);
    perp_and_height(ray, player, win_infos);
    ray->z_buffer[ray->pix] = ray->perp_wall_dist;
    texturisation(ray, win_infos);
    ray->pix++;
}

int raycasting(
    t_params *win_infos)
{
    t_ray *ray;

    if (!(ray = malloc(sizeof(t_ray))))
        return (-1);
    ft_bzero(ray, sizeof(t_ray));
    if (!(ray->z_buffer = malloc(sizeof(double) * win_infos->info->scren_with)))
        return (-1);
    ft_bzero(ray->z_buffer, sizeof(double) * win_infos->info->scren_with);
    while (ray->pix < win_infos->info->scren_with)
        do_raycasting(win_infos, ray);
    mlx_put_image_to_window(win_infos->mlx, win_infos->window, win_infos->img->ptr, 0, 0);
    free(ray->z_buffer);
    free(ray);
    return (1);
}

int set_texture(
    t_params *win_infos,
    char *path,
    int texture_index)
{
    win_infos->tex[texture_index]->img_ptr =
        mlx_xpm_file_to_image(win_infos->mlx, "mossy.xpm", &win_infos->tex[texture_index]->width, &win_infos->tex[texture_index]->height);
    // win_infos->tex[texture_index]->data =
    //     mlx_get_data_addr(win_infos->tex[texture_index]->img_ptr,
    //                       &win_infos->tex[texture_index]->bpp,
    //                       &win_infos->tex[texture_index]->size_line,
    //                       &win_infos->tex[texture_index]->endian);
    // if (win_infos->tex[texture_index]->img_ptr)
    // {
    //     write(1, "GGP", 3);
    // }
    // else
    // {
    //     write(1, "ff", 3);
    // }

    mlx_put_image_to_window(win_infos->mlx, win_infos->window, win_infos->tex[texture_index]->img_ptr, 100, 1100);
    return (1);
}

int main(void)
{

    t_params *params;
    t_img *img_stuct;
    t_ray *ray;
    double time = 0;
    double oldTime = 0;

    params = (t_params *)malloc(sizeof(t_params) + 1);
    params->info = malloc(sizeof(t_info) + 1);
    params->fd = open("map.cub", O_RDONLY);

    get_Resolution(params);
    get_map(params);
    //ft_texturing(params);
    int count = 0;
    params->tex = malloc(sizeof(t_tex));
    while (count < 4)
    {
        if (!(params->tex[count] = malloc(sizeof(t_tex))))
            return (-1);
        ft_bzero(params->tex[count], sizeof(t_tex));
        count++;
    }

    // set_texture(params, "hit.xpm", 1);
    if (!(params->player = malloc(sizeof(t_player))))
        return (-1);
    params->mlx = mlx_init();
    params->window = mlx_new_window(params->mlx, params->info->scren_with, params->info->scren_height, "cub3D");
    img_stuct = (t_img *)malloc(sizeof(t_img));
    void *img_mlx;
    img_mlx = mlx_new_image(params->mlx, params->info->scren_with, params->info->scren_with);
    create_img(img_stuct, img_mlx, params);
    set_texture(params, "mossy.xpm", 0);
    ft_bzero(params->player, sizeof(t_player));
    params->player->posx = 1;
    params->player->posy = 1;
    params->player->speed = 0.14;
    params->player->dir_x = -1.0;
    params->player->dir_y = 0;
    params->player->plane_x = 0.0;
    params->player->plane_y = 0.66;
    params->player->rotate_speed = 0.10;
    params->posX = params->player->posx;
    params->posY = params->player->posy;
    params->planeX = params->player->plane_x;
    params->planeY = params->player->plane_y;
    params->dirX = params->player->dir_x;
    params->dirY = params->player->dir_y;
    params->img = img_stuct;
    // set_texture(params, "egle.xpm", 2);
    // set_texture(params, "blue.xpm", 3);
    //draw_background(params);
    //drd(params);
    //raycasting(params);
    mlx_put_image_to_window(params->mlx, params->window, params->img->img_mlx, 0, 0);
    mlx_hook(params->window, 2, (1L << 0), presskey, params);
    mlx_loop(params->mlx);

    return (0);
}
void verLine(t_vline vline, t_img *img, t_params *prams)
{
    t_point *p1;
    t_point *p2;

    p1 = (t_point *)malloc(sizeof(t_point));
    p2 = (t_point *)malloc(sizeof(t_point));
    p1->colour = vline.colour;
    p2->colour = vline.colour;
    p1->x = vline.x;
    p2->x = vline.x;
    p1->y = vline.start;
    p2->y = vline.end;
    make_img_line(p1, p2, img, prams);
    free(p1);
    free(p2);
}

// int set_texture(
//     t_params *win_infos,
//     const char *path,
//     int texture_index)
// {
//     if (!(win_infos->tex[texture_index]->img_ptr =
//               mlx_xpm_file_to_image(win_infos->mlx, (char *)path,
//                                     &win_infos->tex[texture_index]->width,
//                                     &win_infos->tex[texture_index]->height)))
//         return (-1);
//     win_infos->tex[texture_index]->data =
//         mlx_get_data_addr(win_infos->tex[texture_index]->img_ptr,
//                           &win_infos->tex[texture_index]->bpp,
//                           &win_infos->tex[texture_index]->size_line,
//                           &win_infos->tex[texture_index]->endian);
//     return (1);
// }

int drd(t_params *params)
{
    t_point *line;
    t_ray *ray;
    double time = 0;
    double oldtime = 0;
    if (!(ray = malloc(sizeof(t_ray))))
        return (-1);
    ft_bzero(ray, sizeof(t_ray));
    if (!(ray->z_buffer = malloc(sizeof(double) * params->info->scren_with)))
        return (-1);
    ft_bzero(ray->z_buffer, sizeof(double) * params->info->scren_with);

    int **world = params->world_map;
    ray->pix = 0;
    while (ray->pix < params->info->scren_with)
    {

        ray->camera_x = (2 * ray->pix) / (double)params->info->scren_with - 1;
        ray->ray_dir_x = params->player->dir_x + params->player->plane_x * ray->camera_x;
        ray->ray_dir_y = params->player->dir_y + params->player->dir_y * ray->camera_x;
        ray->mapx = (int)params->posX;
        ray->mapy = (int)params->posY;
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
        ray->hit = 0;
        if (ray->ray_dir_x < 0)
        {
            ray->step_x = -1;
            ray->side_dist_x = (params->player->posx - ray->mapx) * ray->delta_dist_x;
        }
        else
        {
            ray->step_x = 1;
            ray->side_dist_x = (ray->mapx + 1.0 - params->player->posx) * ray->delta_dist_x;
        }
        if (ray->ray_dir_y < 0)
        {
            ray->step_y = -1;
            ray->side_dist_y = (params->player->posy - ray->mapy) * ray->delta_dist_y;
        }
        else
        {
            ray->step_y = 1;
            ray->side_dist_y = (ray->mapy + 1.0 - params->player->posy) * ray->delta_dist_y;
        }
        while (ray->hit == 0)
        {
            if (ray->side_dist_x < ray->side_dist_y)
            {
                ray->side_dist_x += ray->delta_dist_x;
                ray->mapx += ray->step_x;
                if (ray->step_x == 1)
                    ray->side = 0;
                else if (ray->step_x == -1)
                    ray->side = 1;
            }
            else
            {
                ray->side_dist_y += ray->delta_dist_y;
                ray->mapy += ray->step_y;
                if (ray->step_y == 1)
                    ray->side = 2;
                else if (ray->step_y == -1)
                    ray->side = 3;
            }
            if (world[ray->mapx][ray->mapy] > 0)
                ray->hit = 1;
        }
        if (ray->side == 0 || ray->side == 1)
            ray->perp_wall_dist = (ray->mapx - params->player->posx + (1 - ray->step_x) / 2) / ray->ray_dir_x;
        else
            ray->perp_wall_dist = (ray->mapy - params->player->posy + (1 - ray->step_y) / 2) / ray->ray_dir_y;
        ray->line_height = (int)(params->info->scren_height / ray->perp_wall_dist);
        ray->draw_start = -ray->line_height / 2 + params->info->scren_height / 2;
        if (ray->draw_start < 0)
            ray->draw_start = 0;
        ray->draw_end = ray->line_height / 2 + params->info->scren_height / 2;
        if (ray->draw_end >= params->info->scren_height)
            ray->draw_end = params->info->scren_height - 1;
        ray->z_buffer[ray->pix] = ray->perp_wall_dist;
        //texture
        if (!(line = malloc(sizeof(t_point))))
            return (-1);
        ft_bzero(line, sizeof(t_point));
        line->x = ray->pix;
        double wall_x;
        if (ray->side == 0 || ray->side == 1)
            wall_x = params->player->posy + ray->perp_wall_dist * ray->ray_dir_y;
        else
            wall_x = params->player->posx + ray->perp_wall_dist * ray->ray_dir_x;
        wall_x -= floor(wall_x);
        //ft_putnb(params->world_map[0][1]);
        if (world[ray->mapx][ray->mapy] == 1)
        {
            t_tex *tex;
            int tex_x;

            tex = params->tex[0];
            if (ray->side == 1)
                tex = params->tex[0];
            if (ray->side == 2)
                tex = params->tex[0];
            if (ray->side == 3)
                tex = params->tex[0];
            tex_x = (int)(wall_x * (double)tex->width);
            if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
                tex_x = tex->width - tex_x - 1;
            if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
                tex_x = tex->width - tex_x - 1;
            line->y0 = ray->draw_end;
            line->y1 = ray->draw_start;
            line->tex_x = tex_x;
            int y_max = 0;
            line->y;
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
            int d = 0;

            if (line->y >= 0)
            {
                y_max = 4;
                line->y = 1;

                while (line->y < y_max)
                {
                    write(1, "HELO", 5);
                    d = line->y * tex->size_line - params->info->scren_height * tex->size_line / 2 + ray->line_height * tex->size_line / 2;
                    line->tex_y = ((d * tex->height) / ray->line_height) / tex->size_line;
                    //params->texx->data[] = 10;
                    // params->texx->data[line->y * params->img->size_line + line->x * params->texx->bpp / 8 + 1] = tex->data[line->tex_y * tex->size_line + line->tex_x * (tex->bpp / 8) + 1];
                    // params->texx->data[line->y * params->img->size_line + line->x * params->texx->bpp / 8 + 2] = tex->data[line->tex_y * tex->size_line + line->tex_x * (tex->bpp / 8) + 2];
                    line->y++;
                    //ft_putnb(params->texx->bpp);

                    //put_pixel_to_image(line, params->img);
                }
            }

            line->y0 = 0;
            line->y1 = ray->draw_start;
            line->y0 = params->info->scren_height;
            line->y1 = ray->draw_end;
        }
        ray->pix++;
    }
    oldtime = time;
    time = 60;
    double frameTime = (time - oldtime) / 20;
    double moveSpeed = frameTime * 3.0;
    double rotSpeed = frameTime * 0.4;
    params->moveSpeed = params->player->speed;
    params->rotSpeed = rotSpeed;
    return (0);
}

int close_window(int key)
{
    putchar(key);
    return (EXIT_SUCCESS);
}

int draw(t_params *params)
{
    int **worldMap = params->world_map;
    int x = 0;

    double time = 0;    //time of current frame
    double oldTime = 0; //time of previous frame
    while (x < params->info->scren_with)
    {
        double cameraX = 2 * x / (double)params->info->scren_with - 1;
        double rayPosX = params->posX;
        double rayPosY = params->posY;
        double rayDirX = params->dirX + params->planeX * cameraX;
        double rayDirY = params->dirY + params->planeY * cameraX;

        int mapX = (int)rayPosX;
        int mapY = (int)rayPosY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        int side_c = 0;
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (rayPosX - mapX) * deltaDistX;
            side_c = 1;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
            side_c = 2;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (rayPosY - mapY) * deltaDistY;
            side_c = 3;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
            side_c = 4;
        }
        side_c = 0;
        while (hit == 0)
        {

            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                if (stepX > 0)
                    side_c = 1;
                if (stepX < 0)
                    side_c = 2;
                params->side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;

                if (stepY > 0)
                    side_c = 3;
                if (stepY < 0)
                    side_c = 4;

                params->side = 1;
            }
            if (worldMap[mapX][mapY] > 0)
                hit = 1;
        }
        if (params->side == 0)
            perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)((int)params->info->scren_height / perpWallDist);
        // hz
        if (perpWallDist == 0)
            lineHeight = 1000;

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + params->info->scren_height / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + params->info->scren_height / 2;
        if (drawEnd >= params->info->scren_height)
            drawEnd = params->info->scren_height - 1;
        if (params->side == 1)
            params->side = params->color = 0xdd8800;
        else
            params->color = 0x00FF00;
        if (side_c == 1)
            params->color = 0x0aa384;
        if (side_c == 2)
            params->color = 0xa30a0a;
        if (side_c == 3)
            params->color = 0xffffff;
        if (side_c == 4)
            params->color = 0xC79CFF;
        // int texNum = params->world_map[params->info->mapheight][params->info->mapwidth] - 1;
        // double wallX;
        // if (params->side == 1)
        //     wallX = params->posY + perpWallDist * rayDirY;
        // wallX -= floor((wallX));
        // int texX = (int)wallX * (double)texWidth;
        // if (params->side == 0 && rayDirX > 0)
        //     texX = texWidth - texX - 1;
        // if (params->side == 1 && rayDirY < 0)
        //     texX = texWidth - texX - 1;
        // double step = 1.0 * texHeight / lineHeight;
        // // // Starting texture coordinate
        // double texPos = (drawStart - params->info->scren_height / 2 + lineHeight / 2) * step;
        // for (int y = drawStart; y < drawEnd; y++)
        // {

        //     int texY = (y * 2 - params->posY + lineHeight) * (texHeight / 2) / lineHeight;
        //     texPos += step;
        //     if (params->side == 1)
        //     {
        //         color = (color >> 1) & 8355711; // assombrir la couleur
        //     }
        //     //     // make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        // }

        //color = params->cast[texNum][texHeight * texY + texX];
        t_vline line;
        params->perp_wall_dist = perpWallDist;
        line.x = x;
        line.start = drawStart;
        line.end = drawEnd;
        line.colour = params->color;
        verLine(line, params->img, params);
        //texturisation(params);
        //draw_wall(line.x, line.start, line.end, params, rayPosX, rayDirY, perpWallDist);
        x++;
    }
    oldTime = time;
    time = 60;
    double frameTime = (time - oldTime) / 20;
    double moveSpeed = frameTime * 3.0;
    double rotSpeed = frameTime * 0.4;
    params->moveSpeed = params->player->speed;
    params->rotSpeed = rotSpeed;

    mlx_hook(params->window, 2, (1L << 0), presskey, params);
    return (0);
}
