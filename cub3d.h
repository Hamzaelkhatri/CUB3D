//
// Created by Kateryna Storozh on 5/23/17.
//

#ifndef cub3D_cub_H
#define cub3D_cub_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>

#define UP 13
#define DOWN 1
#define ROTRIGHT 124
#define RIGHT 2
#define ROTLEFT 123
#define LEFT 0
#define EXIT 53
#define texWidth 64
#define texHeight 64
#define SCREN_HEIGHT 1280
#define SCREN_WIGHT 1280

typedef struct s_ray
{
    int pix;
    int mapx;
    int mapy;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    double *z_buffer;
} t_ray;

typedef struct s_info
{
    int scren_with;
    int scren_height;
    int mapwidth;
    int mapheight;
} t_info;

typedef struct s_player
{
    double posx;
    double posy;
    double speed;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double rotate_speed;
} t_player;

typedef struct s_img
{
    void *img_mlx;
    char *map;
    unsigned int *adr;
    void *ptr;
    int size_line;
} t_img;

typedef struct s_tex
{
    int width;
    int height;
    int size_line;
    int bpp;
    int endian;
    void *img_ptr;
    char *data;
} t_tex;

typedef struct s_params
{
    void *mlx;
    int fd;
    char *line;
    t_img *img;
    t_img imgs;
    t_info *info;
    t_tex **tex;
    t_tex *texx;
    t_player *player;
    int bitpx;
    void *window;
    int endian;
    int size_line;
    double dirX;
    double dirY;
    double rotSpeed;
    double planeX;
    char **path_wall;
    char **map;
    double planeY;
    double moveSpeed;
    double posX;
    void *img_ptr;
    int perp_wall_dist;
    double posY;
    int color_ceiling;
    int color_floor;
    int lineheight;
    int y_text;
    int x_text;
    int color;
    int id;
    int side;
    char **world_map;

} t_params;

typedef struct s_vline
{
    int x;
    int start;
    int end;
    int colour;
} t_vline;

typedef struct s_print_struct
{
    int steep1;
    int steep2;
    double x0;
    double x1;
    double y0;
    double y1;
    int **rgb;
} t_print_struct;

typedef struct s_point
{
    int x;
    int y;
    int y0;
    int y1;
    int tex_x;
    int tex_y;
    int colour;
} t_point;

typedef struct s_rgb
{
    double r;
    double g;
    double b;
} t_rgb;

int presskey(int keycode, t_params *params);
void draw_background(t_params *params);
void draw_floor(t_params *params);
int returns(char *msg);
void ft_bzero(void *str, size_t n);
int raycasting(t_params *win_infos);
int draw(t_params *params);
void make_img_line(t_point *p1, t_point *p2, t_img *imege, t_params *params);
t_print_struct *init_struct(t_point *p1, t_point *p2);
void print_img_line(t_print_struct *p_s, t_img *img, float t, int x, t_params *params);
int put_pixel_to_image(t_point *p, t_img *image);
int raycasting(t_params *win_infos);

#endif
