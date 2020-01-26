/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 22:20:55 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:28:19 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_first_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != ' ')
			returns("Error\n CHECK THE MAP");
		i++;
	}
}

int		do_condition_tw(t_params *params, int j)
{
	if ((params->line[j] == 'N' ||
				params->line[j] == 'S' || params->line[j] == 'E' ||
				params->line[j] == 'W'))
		return (1);
	else
		return (0);
}

int		do_condition(t_params *params, int j)
{
	if ((params->line[j] == '0' ||
				params->line[j] == '1' || params->line[j] == 'N' ||
				params->line[j] == 'S' || params->line[j] == 'E' ||
				params->line[j] == '2' || params->line[j] == 'W'))
		return (1);
	else
		return (0);
}

void	get_mp(t_params *params, int i)
{
	int y;
	int j;
	int check;

	y = 0;
	j = -1;
	while (y <= (int)params->info->mapwidth - 1 && params->line[++j])
	{
		if (do_condition(params, j) == 1)
		{
			check_map(params->line, params);
			if (do_condition_tw(params, j) == 1)
			{
				params->position = params->line[j];
				(check == 1 ? returns("Error\n CHECK THE MAP") : 0);
				check = 1;
				params->player->posx = y;
				params->player->posy = i;
				params->world_map[i][y] = '0';
			}
			else
				params->world_map[i][y] = params->line[j];
			y++;
		}
	}
}

void	get_map(t_params *params)
{
	int i;
	int y;
	int j;

	i = 0;
	y = 0;
	j = 0;
	params->world_map =
		(char **)malloc(sizeof(char *) * params->info->mapheight + 1);
	(!params->world_map ? returns("\n") : 0);
	get_next_line(params->fd, &params->line);
	while (i < params->info->mapheight &&
			get_next_line(params->fd, &params->line))
	{
		params->world_map[i] =
			(char *)malloc(sizeof(char) * params->info->mapwidth + 1);
		(!params->world_map[i] ? returns("\n") : 0);
		get_mp(params, i);
		(i == 0 ? check_first_line(params->line) : 0);
		i++;
	}
}
