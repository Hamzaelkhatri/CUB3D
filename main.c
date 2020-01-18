/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:40 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/18 03:28:26 by helkhatr         ###   ########.fr       */
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

        nb *= (-1);
    }
    if (nb >= 10)
    {
        ft_putnb(nb / 10);
        ft_putnb(nb % 10);
    }
    else
    {
        putchar('-');
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
    int o;
    char tab[24];
    int j = 0;
    i = 0;
    o = 0;
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
    get_maphe(fd, line, &params->info->mapwidth, &params->info->mapheight);
}

void get_map(t_params *pParams)
{
    int i = 0;
    int y = 0;
    int j;

    pParams->world_map = (char **)malloc(sizeof(char *) * pParams->info->mapheight + 1);
    get_next_line(pParams->fd, &pParams->line);
    get_next_line(pParams->fd, &pParams->line);
    printf("\n");
    while (i < pParams->info->mapheight && get_next_line(pParams->fd, &pParams->line))
    {
        pParams->world_map[i] = (char *)malloc(sizeof(char) * pParams->info->mapwidth + 1);
        j = 0;
        y = 0;

        while (y <= (int)pParams->info->mapwidth - 1 && pParams->line[j])
        {
            if ((pParams->line[j] == '0' || pParams->line[j] == '1' || pParams->line[j] == 'N'))
            {
                if (pParams->line[j] == 'N')
                {
                    pParams->player->posx = i;
                    pParams->player->posy = y;
                }
                else
                {
                    pParams->world_map[i][y] = pParams->line[j];
                }
                y++;
            }
            j++;
        }
        printf("\n");
        i++;
    }
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

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}

int get_texture(t_params *params, char *path, int id)
{
    params->tex[id]->img_ptr = mlx_xpm_file_to_image(params->mlx, path,
                                                     &params->tex[id]->width, &params->tex[id]->height);
    params->tex[id]->data = mlx_get_data_addr(params->tex[id]->img_ptr,
                                              &params->tex[id]->bpp, &params->tex[id]->size_line, &params->tex[id]->endian);
    return (0);
}

int ft_strncmp(const char *str1, const char *str2, size_t n)
{
    if (n == 0)
        return (0);
    while (0 < n && (*str1 != '\0' || *str2 != '\0'))
    {
        if ((unsigned char)*str1 != (unsigned char)*str2)
        {
            return ((unsigned char)*str1 - (unsigned char)*str2);
        }
        n--;
        str1++;
        str2++;
    }
    return (0);
}

void check_name_map(char *path, t_params *params)
{
    int i;
    i = ft_strlen(path);
    if (ft_strncmp(".cub", &path[i - 4], 3) != 0)
    {
        returns("Error\n PLEASE CHECK EXTENTION OF MAP FILE");
        exit(0);
    }
    else
    {
        params->fd = open(path, O_RDONLY);
    }
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void check_ac(int ac)
{
    if (ac < 2)
        returns("Error\n PLEASE ADD ARGUMENT OF MAP");
}

void ft_putstr(char const *s)
{
    int i;

    i = 0;
    if (s)
    {
        while (s[i] != '\0')
        {
            ft_putchar(s[i]);
            i++;
        }
    }
}

int returns(char *msg)
{
    ft_putstr(msg);
    exit(0);
}

int main(int ac, char **ag)
{

    t_params *params;
    t_img *img_stuct;
    t_ray *ray;
    double time = 0;
    double oldTime = 0;

    params = (t_params *)malloc(sizeof(t_params) + 1);
    params->info = malloc(sizeof(t_info) + 1);
    check_ac(ac);
    check_name_map(ag[1], params);
    if (!(params->player = malloc(sizeof(t_player))))
        return (-1);
    ft_bzero(params->player, sizeof(t_player));
    get_Resolution(params);

    get_map(params);
    int count = 0;
    params->tex = malloc(sizeof(t_tex));
    if (!(params->texx = malloc(sizeof(t_tex))))
        return (returns("EROR\n"));
    ft_bzero(params->texx, sizeof(t_tex));
    while (count < 4)
    {
        if (!(params->tex[count] = malloc(sizeof(t_tex))))
            return (-1);
        ft_bzero(params->tex[count], sizeof(t_tex));
        count++;
    }

    params->mlx = mlx_init();
    params->window = mlx_new_window(params->mlx, params->info->scren_with, params->info->scren_height, "cub3D");
    img_stuct = (t_img *)malloc(sizeof(t_img));
    void *img_mlx;
    if (!(params->texx->img_ptr = mlx_new_image(params->mlx, params->info->scren_with, params->info->scren_height)))
    {
        returns("EREUR");
    }
    params->texx->data = mlx_get_data_addr(params->texx->img_ptr,
                                           &params->texx->bpp, &params->texx->size_line, &params->texx->endian);
    params->texx->width = params->info->scren_with;
    params->texx->height = params->info->scren_height;

    get_texture(params, "mossy.xpm", 0);
    get_texture(params, "north.xpm", 1);
    get_texture(params, "egle.xpm", 2);
    get_texture(params, "blue.xpm", 3);

    params->player->posx = 1;
    params->player->posy = 1;
    params->player->speed = 0.66;
    params->player->dir_x = -1;
    params->player->dir_y = 0;
    params->player->plane_x = 0;
    params->player->plane_y = 0.66;
    params->player->rotate_speed = 0.06;
    mlx_loop_hook(params->mlx, raycasting, params);
    raycasting(params);
    mlx_hook(params->window, 2, 0, presskey, params);
    mlx_loop(params->mlx);

    return (0);
}
int close_window(int key)
{
    putchar(key);
    return (EXIT_SUCCESS);
}