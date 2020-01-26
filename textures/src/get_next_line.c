/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:26:59 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;
	int		i;

	len = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[len])
		len++;
	while (s2[i])
		i++;
	str = ft_calloc(len + i);
	if (str == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		str[len] = s1[len];
		len += 1;
	}
	str[len] = '\0';
	ft_strcat(str, s2);
	return (str);
}

static int		gline(char **s, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_strsub(*s, 0, len);
		tmp = ft_strdup(&((*s)[len + 1]));
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			freez(s);
	}
	else
	{
		*line = ft_strdup(*s);
		freez(s);
	}
	return (1);
}

static char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

static int		returs(char **s, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (s[1] == NULL && ret == 0)
	{
		*line = ft_strdup("\0");
		return (0);
	}
	else
		return (gline(&s[fd], line));
}

int				get_next_line(const int fd,
		char **line)
{
	int				ret;
	static char		*str[2];
	char			*buff;
	char			*tmp;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buff == NULL || fd < 0 ||
			line == NULL || fd > 4864 || read(fd, buff, 0))
		return (freez(&buff));
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (str[1] == NULL)
			str[1] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str[1], buff);
			free(str[1]);
			str[1] = tmp;
		}
		if (ft_strchr(str[1], '\n'))
			break ;
	}
	freez(&buff);
	return (returs(str, line, ret, 1));
}
