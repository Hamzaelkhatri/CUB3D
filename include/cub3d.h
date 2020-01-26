/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 02:38:49 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 03:04:38 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <sys/types.h>
# include <sys/uio.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# define BUFFER_SIZE 128
# define UP 13
# define DOWN 1
# define ROTRIGHT 124
# define RIGHT 2
# define ROTLEFT 123
# define LEFT 0
# define EXIT 53
# define R 8
# define G 9
# define B 10

typedef struct			s_ray
{
	int					pix;
	int					mapx;
	int					mapy;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				*buffer;
}						t_ray;

typedef struct			s_sprite
{
	int					x;
	int					y;
}						t_sprite;

typedef struct			s_sprites
{
	int					x;
	int					y;
	struct s_sprites	*next;
}						t_sprites;

typedef struct			s_draw_sprite
{
	t_sprite			*sprites;
	int					i;
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_width;
	int					draw_start_x;
	int					draw_end_x;
	int					stripe;
	int					y;
	int					d;
	int					tex_x;
	int					tex_y;
	int					color;
	int					totcolor;
}						t_draw_sprite;

typedef struct			s_info
{
	int					scren_with;
	int					scren_height;
	int					mapwidth;
	int					mapheight;
}						t_info;

typedef struct			s_player
{
	double				posx;
	double				posy;
	double				speed;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				rotate_speed;
	double				cam_height;
	int					health;
}						t_player;

typedef struct			s_img
{
	void				*img_mlx;
	char				*map;
	unsigned int		*adr;
	void				*ptr;
	int					size_line;
}						t_img;

typedef struct			s_tex
{
	int					width;
	int					height;
	int					size_line;
	int					bpp;
	int					endian;
	void				*img_ptr;
	unsigned char		*data;
}						t_tex;

typedef struct			s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct			s_position
{
	int					n;
	int					s;
	int					w;
	int					e;
}						t_position;

typedef struct			s_key
{
	int					d;
	int					u;
	int					r;
	int					l;
	int					ror;
	int					rol;
	int					e;
}						t_key;

typedef struct			s_params
{
	void				*mlx;
	char				position;
	int					fd;
	char				*path_so;
	char				*path_no;
	char				*path_es;
	char				*path_we;
	char				*path_sprite;
	char				*path;
	char				*line;
	t_img				*img;
	t_img				imgs;
	t_info				*info;
	t_tex				**tex;
	t_tex				*texx;
	t_tex				*sprite;
	t_tex				*floors;
	t_player			*player;
	t_key				key;
	t_sprites			*sprites;
	int					keycode;
	int					bitpx;
	void				*window;
	int					endian;
	int					size_line;
	char				**path_wall;
	char				**map;
	void				*img_ptr;
	int					perp_wall_dist;
	int					ceil;
	int					floor;
	int					lineheight;
	int					y_text;
	int					x_text;
	int					color;
	int					id;
	int					side;
	char				**world_map;
}						t_params;

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct			s_print_struct
{
	int					steep1;
	int					steep2;
	double				x0;
	double				x1;
	double				y0;
	double				y1;
	int					**rgb;
}						t_print_struct;

typedef struct			s_point
{
	int					x;
	int					y;
	int					y0;
	int					y1;
	int					tex_x;
	int					tex_y;
	int					colour;
}						t_point;

char					*ft_strcat(char *s1, const char *s2);
char					*ft_calloc(size_t size);
int						freez(char **as);
char					*ft_strsub(char const *s,
						unsigned int start, size_t len);
char					*ft_strdup(const char *s1);
int						get_next_line(const int fd, char **line);
int						res(int keycode, t_params *params);
int						presskey(int keycode, t_params *params);
void					draw_background(t_params *params);
int						draw_sprite(t_ray *ray, t_params *params);
unsigned long			rgb_to_hex(int r, int g, int b);
void					draw_floor(t_params *params);
int						returns(char *msg);
void					init_key(t_params *params);
void					ft_bzero(void *str, size_t n);
void					press_down(t_params *params);
void					realse(t_params *params);
void					ft_putchar(char c);
void					press_left(t_params *params);
void					*ft_memset(void *b, int c, size_t len);
void					open_win(t_params *params);
void					press_rotleft(t_params *params);
void					press_right(t_params *params);
size_t					ft_strlen(const char *str);
int						ft_strncmp(const char *str1,
						const char *str2, size_t n);
int						get_texture(t_params *params, char *path, int id);
void					press_up(t_params *params);
int						ft_strncmp(const char *str1,
						const char *str2, size_t n);
void					check_name_map(char *path, t_params *params);
void					get_maphe(t_params *params, int fd);
void					ft_putstr(char const *s);
void					get_resolution(t_params *params);
void					get_ciel_color(t_params *params);
void					get_floor_color(t_params *params);
int						ft_height(t_params *parms);
void					get_no_texture(t_params *params);
void					ft_bzero(void *str, size_t n);
void					init_player(t_params *params);
void					check_map(char *str, t_params *params);
int						ft_isdigit(char c);
int						returns(char *msg);
int						update(t_params *params);
size_t					ft_strlen_w(const char *str);
void					init_tex_sprite(t_params *params);
void					texture_position(t_params *params);
void					get_so_texture(t_params *params);
void					get_we_texture(t_params *params);
size_t					ft_strlcpy(char *dst, const char *src);
void					textures_path(t_position *pos, t_params *params);
void					hit(t_ray *ray, t_params *params);
int						ini_image(t_params *params);
void					ft_calc(t_draw_sprite *ds, t_params *params);
int						presskey(int keycode, t_params *params);
int						main(int ac, char **ag);
void					steps(t_ray *ray, t_player *player);
void					get_ea_texture(t_params *params);
void					gnl(int fd, t_params *params);
void					press_rotright(t_params *params);
int						ft_close(t_params *params);
int						ft_width_map(char *str);
void					check_ac(int ac);
int						ft_atoi(char *str);
void					texture_on_img(t_point *line, t_tex *texture
						, t_params *params, t_ray *ray);
void					get_height(char *str, int *h);
void					set_texture(t_ray *ray, t_params *params);
void					get_sprite(t_params *params);
void					init_ray(t_ray *ray, t_player *player,
						t_params *params);
int						ini_params(t_params *params);
int						set_sprite(char *path, t_params *params);
t_sprite				*list_to_tab(t_params *params);
size_t					ft_strlen(const char *str);
void					raycasting_tw(t_params *params, t_ray *ray);
void					perp_and_height(t_ray *ray, t_player *player,
						t_params *params);
int						draw(t_params *params);
void					hud_tex(t_params *params);
void					get_map(t_params *params);
void					make_img_line(t_point *p1, t_point *p2,
						t_img *imege, t_params *params);
void					print_img_line(t_print_struct *p_s, t_img *img,
						float t, int x, t_params *params);
int						put_pixel_to_image(t_point *p, t_img *image);
void					sort_sprite(t_params *params, t_sprite *sprites,
						int nbr_sprites);
int						draw(t_params *params);
char					*ft_strjoin(char const *s1, char const *s2);
void					is_sprite(t_ray *ray, t_params *params);
int						ft_lstsize(t_list *lst);
int						set_sprite(char *path, t_params *params);
int						create_bitmap(t_tex *mlx_img, char *path);
char					*ft_strjoin(char const *s1, char const *s2);
void					get_sides(t_ray *ray);
void					next_sprite(t_sprites *actual, t_sprites *new,
						t_ray *ray);

#endif
