/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realisation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:09:10 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 00:27:51 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_close(t_params *params)
{
	(void)params;
	exit(0);
}

int		update(t_params *params)
{
	if (params->key.r == 1)
		press_right(params);
	if (params->key.l == 1)
		press_left(params);
	if (params->key.d == 1)
		press_down(params);
	if (params->key.u == 1)
		press_up(params);
	if (params->key.e == 1)
	{
		exit(1);
	}
	if (params->key.ror == 1)
		press_rotright(params);
	if (params->key.rol == 1)
		press_rotleft(params);
	if (params->key.rol == 1 || params->key.ror == 1 ||
			params->key.l || params->key.d == 1 ||
			params->key.u == 1 || params->key.r == 1)
		realse(params);
	return (0);
}
