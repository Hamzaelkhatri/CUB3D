/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:22:15 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:19:56 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		data_to_bitmap(t_tex *img, int fd)
{
	int i;

	i = img->width * img->height - 1;
	while (i >= 0)
	{
		write(fd, &img->data[i * img->bpp / 8], 4);
		i--;
	}
	return (1);
}

void	write_verti_pixel(t_tex *mlx_img, int i, int *c, int b)
{
	char	save;
	int		k;

	k = 3;
	while (k >= 0)
	{
		save = mlx_img->data[*c + (i * mlx_img->size_line)];
		mlx_img->data[*c + (i * mlx_img->size_line)] =
			mlx_img->data[b - k + (i * mlx_img->size_line - 1)];
		mlx_img->data[b - k + (i * mlx_img->size_line - 1)] = save;
		k--;
		*c = *c + 1;
	}
}

int		mir_verti(t_tex *mlx_img)
{
	int i;
	int c;
	int size_line;

	i = 0;
	while (i < mlx_img->height)
	{
		c = 0;
		size_line = mlx_img->size_line;
		while (c < size_line && c != size_line)
		{
			write_verti_pixel(mlx_img, i, &c, size_line);
			size_line -= 4;
		}
		i++;
	}
	return (0);
}

int		bitmap_info_header(t_tex *mlx_img, int fd)
{
	int header_info_size;
	int plane_nbr;
	int o_count;

	header_info_size = 40;
	plane_nbr = 1;
	write(fd, &header_info_size, 4);
	write(fd, &mlx_img->width, 4);
	write(fd, &mlx_img->height, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &mlx_img->bpp, 2);
	o_count = 0;
	while (o_count < 28)
	{
		write(fd, "\0", 1);
		o_count++;
	}
	return (1);
}

int		create_bitmap(t_tex *mlx_img, char *path)
{
	int fd;
	int file_size;
	int first_pix;

	fd = open(path, O_CREAT | O_RDWR);
	if (fd < 0)
		returns("error\nacces denied");
	file_size = 14 + 40 + 4 + (mlx_img->width * mlx_img->height) * 4;
	first_pix = 14 + 40 + 4;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	bitmap_info_header(mlx_img, fd);
	mir_verti(mlx_img);
	data_to_bitmap(mlx_img, fd);
	close(fd);
	return (1);
}
