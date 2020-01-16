#include "cub3d.h"
#include "mlx.h"
#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// int ft_texture(t_params *stock)
// {
// 	if (ft_path_wall(stock) == 0)
// 		return (0);
// 	return (1);
// }

// int ft_texturing(t_params *stock)
// {
// 	int i;

// 	i = -1;
// 	if (!(stock->mlx_wall = malloc(sizeof(int *) * 4)) ||
// 		!(stock->cast = malloc(sizeof(int *) * 4)))
// 		return (0);
// 	while (++i < 4)
// 	{
// 		if (((stock->mlx_wall[i] = mlx_xpm_file_to_image(stock->mlx,
// 														 stock->path_wall[i], &stock->info->mapwidth, &stock->info->mapheight)) <= 0))
// 			return (0);
// 		if (((stock->cast[i] = (int *)mlx_get_data_addr(stock->mlx_wall[i],
// 														&stock->bitpx, &stock->size_line, &stock->endian)) <= 0))
// 			return (0);
// 	}
// 	return (1);
// }

int main(void)
{
    void *mlx_ptr;
    void *mlx_win;
    mlx_ptr = mlx_init();
    int w = 1200;
    int h = 1200;
    int tab[4];
    mlx_win = mlx_new_window(mlx_ptr, h, 1200, "IMAGE");
    void *ptr = mlx_xpm_file_to_image(mlx_ptr, "mossy.xpm", &w, &h);
    //mlx_xpm_to_image(mlx_ptr, img, &w, &h);
    void *adr = mlx_get_data_addr(ptr, &tab[1], &tab[2], &tab[3]);
    mlx_put_image_to_window(mlx_ptr, mlx_win, adr, 1000, 1000);
    mlx_loop(mlx_ptr);
}
