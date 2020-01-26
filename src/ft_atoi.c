/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:19:11 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void			ft_calc(t_draw_sprite *ds, t_params *params)
{
	if (ds->draw_start_x < 0)
		ds->draw_start_x = 0;
	ds->draw_end_x = ds->sprite_width / 2 + ds->sprite_screen_x;
	if (ds->draw_end_x >= params->info->scren_with)
		ds->draw_end_x = params->info->scren_with - 1;
	ds->stripe = ds->draw_start_x;
}

void			get_height(char *str, int *h)
{
	int		j;
	int		i;
	char	tab2[24];

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

void			*ft_memcpy(void *dest, void const *scr, size_t n)
{
	int						i;
	char					*destmp;
	const unsigned char		*srctmp;

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

static int		operation(const char *str, int i, int l, int sign)
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

int				ft_atoi(char *str)
{
	size_t	i;
	int		sign;
	int		l;

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
