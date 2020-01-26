/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:22:19 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:23:08 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			is_sprite(
		t_ray *ray,
		t_params *params)
{
	t_sprites *new;
	t_sprites *actual;
	t_sprites tmp;

	if (!(new = malloc(sizeof(t_sprites))))
		returns("error \nPROBLEM IN ALLOCATION");
	ft_bzero(new, sizeof(t_sprites));
	new->next = NULL;
	new->x = ray->mapx;
	new->y = ray->mapy;
	actual = params->sprites;
	tmp = *actual;
	if (actual->x == -1 && actual->y == -1)
	{
		actual->x = ray->mapx;
		actual->y = ray->mapy;
	}
	else
		next_sprite(actual, new, ray);
	actual = &tmp;
}

int				ft_lstsize(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void			sort_sprite(
		t_params *params,
		t_sprite *sprites,
		int nbr_sprites)
{
	int			i;
	double		dist_one;
	double		dist_two;
	t_sprite	tmp;

	i = 0;
	while (i < nbr_sprites && i + 1 != nbr_sprites)
	{
		dist_one = ((params->player->posx
		- sprites[i].x) * (params->player->posx
		- sprites[i].x) + (params->player->posy
		- sprites[i].y) * (params->player->posy - sprites[i].y));
		dist_two = ((params->player->posx - sprites[i + 1].x)
		* (params->player->posx - sprites[i + 1].x)
		+ (params->player->posy
		- sprites[i + 1].y) * (params->player->posy - sprites[i + 1].y));
		if (dist_one < dist_two)
		{
			tmp = sprites[i];
			sprites[i] = sprites[i + 1];
			sprites[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

t_sprite		*list_to_tab(
		t_params *params)
{
	t_sprite	*rtn;
	t_sprites	*tmp;
	int			count;

	tmp = params->sprites;
	count = -1;
	if (!(rtn = malloc(sizeof(t_sprite)
					* ft_lstsize((t_list *)params->sprites))))
		return (0);
	ft_bzero(rtn, sizeof(t_sprite));
	while (++count > -1)
	{
		if (params->sprites)
		{
			rtn[count].x = params->sprites->x;
			rtn[count].y = params->sprites->y;
		}
		if (params->sprites->next)
			params->sprites = params->sprites->next;
		else
			break ;
	}
	params->sprites = tmp;
	return (rtn);
}
