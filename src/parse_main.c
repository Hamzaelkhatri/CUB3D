/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:38:52 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_resolution_tw(t_params *params, int i, int fd)
{
	get_height(params->line + i, &params->info->scren_height);
	if (params->info->scren_with == 0 || params->info->scren_height == 0 ||
			(params->info->scren_with > 4096 ||
			params->info->scren_height > 3000))
		returns("EROR\n PLEASE CHECK THE RESOLUTION OF MAP ");
	free(params->line);
	get_maphe(params, fd);
}

void	get_maphe(t_params *params, int fd)
{
	int len;

	len = 0;
	gnl(fd, params);
	while (get_next_line(fd, &params->line))
	{
		params->info->mapwidth = ft_strlen_w(params->line);
		len++;
		free(params->line);
	}
	params->info->mapheight = len;
	close(fd);
}

void	check_resolution(char *str)
{
	int i;

	i = 1;
	if (str[0] != 'R')
		returns("Error\nCHECK THE RESOLUTION");
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
		{
			returns("Error\nCHECK THE RESOLUTION");
			i++;
		}
		i++;
	}
}

void	get_resolu(t_params *params, int i, int fd, char *tab)
{
	params->info->scren_with = ft_atoi(tab);
	get_resolution_tw(params, i, fd);
}

void	get_resolution(t_params *params)
{
	int		fd;
	int		i;
	int		o;
	char	tab[24];
	int		j;

	i = 0;
	j = 0;
	fd = open(params->path, O_RDONLY);
	get_next_line(fd, &params->line);
	check_resolution(params->line);
	while (params->line[i] != '\0')
	{
		if (ft_isdigit(params->line[i]))
		{
			tab[j] = params->line[i];
			(params->line[i + 1] == ' ' ? o = 1 : 0);
			j++;
		}
		if (o == 1)
			break ;
		i++;
	}
	tab[j] = '\0';
	get_resolu(params, i, fd, tab);
}
