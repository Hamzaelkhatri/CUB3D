/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:12:08 by kstorozh          #+#    #+#             */
/*   Updated: 2020/01/14 23:18:53 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void freeztable(void **arrey, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arrey[i] != NULL)
			free(arrey[i]);
		i++;
	}
	if (arrey != NULL)
		free(arrey);
}

void swap(double *x1, double *x2)
{
	double i;
	double j;

	i = *x1;
	j = *x2;
	*x1 = j;
	*x2 = i;
}

void create_img(t_img *img_struct, void *img_mlx, t_params *params)
{
	int bit_per_pixel;
	int size_line;
	int endian;
	void *img;
	img_struct->map = mlx_get_data_addr(img_mlx, &params->bitpx, &size_line, &endian);
	img_struct->size_line = size_line;
	img_struct->img_mlx = img_mlx;
}
