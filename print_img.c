/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:44:18 by kstorozh          #+#    #+#             */
/*   Updated: 2020/01/15 00:27:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include <mlx.h>

void make_img_line(t_point *p1, t_point *p2, t_img *imege, t_params *params)
{
	t_print_struct *ps;

	if ((ps = init_struct(p1, p2)) == NULL)
		return;
	if (fabs(ps->x0 - ps->x1) < fabs(ps->y0 - ps->y1))
	{
		swap(&ps->x0, &ps->y0);
		swap(&ps->x1, &ps->y1);
		ps->steep1 = 1;
	}
	if (ps->x0 > ps->x1)
	{
		swap(&ps->x0, &ps->x1);
		swap(&ps->y0, &ps->y1);
		ps->steep2 = 1;
	}
	print_img_line(ps, imege, 0, 0, params);
}

t_print_struct *init_struct(t_point *p1, t_point *p2)
{
	t_print_struct *print_struct;

	if ((print_struct = (t_print_struct *)malloc(sizeof(t_print_struct))) == NULL)
		return (NULL);
	print_struct->steep1 = 0;
	print_struct->steep2 = 0;
	print_struct->x0 = p1->x;
	print_struct->x1 = p2->x;
	print_struct->y0 = p1->y;
	print_struct->y1 = p2->y;
	if ((print_struct->rgb = (int **)malloc(sizeof(int *) * 3)) == NULL)
		return (NULL);
	print_struct->rgb[0] = c_rgb(p1->colour);
	print_struct->rgb[1] = c_rgb(p2->colour);
	return (print_struct);
}

void print_img_line(t_print_struct *p_s, t_img *img, float t, int x, t_params *params)
{
	int y;
	t_point *point;
	double **couleur_matrix;

	point = (t_point *)malloc(sizeof(t_point));
	x = (int)p_s->x0;
	couleur_matrix = create_gradient(p_s->rgb, p_s->x1 - p_s->x0, params);

	while (x <= p_s->x1)
	{
		(p_s->steep2 == 1) ? delcouleur(couleur_matrix, point) : addcouleur(couleur_matrix, point);
		t = (float)((x - p_s->x0) /
					(float)(p_s->x1 - p_s->x0));
		y = (int)(p_s->y0 * (1.0 - t) + p_s->y1 * t);
		point->x = (p_s->steep1) ? y : x;
		point->y = (p_s->steep1) ? x : y;
		put_pixel_to_image(point, img);
		x++;
	}
}

int put_pixel_to_image(t_point *p, t_img *image)
{
	int col;
	int k;
	char *map;
	int size_line;

	col = p->colour;
	map = image->map;
	size_line = image->size_line;
	if (p->x >= SCREN_WIGHT || p->y >= SCREN_HEIGHT || p->x < 0 || p->y < 0)
		return (-1);
	k = (int)((p->y) * size_line + (p->x) * 4);
	if (k >= SCREN_HEIGHT * size_line * 4 - 1)
		return (-1);
	else if (k < 0)
		return (-1);
	map[k] = (unsigned char)(col & 0xFF);
	k++;
	map[k] = (unsigned char)(col >> 8 & 0xFF);
	k++;
	map[k] = (unsigned char)(col >> 16 & 0xFF);
	return (0);
}
