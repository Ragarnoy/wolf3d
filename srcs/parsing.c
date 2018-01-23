/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:06:22 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 17:20:57 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	clean_exit(int error, char **s)
{
	free(s);
//	while (s[++i])
	exit_prog(error);
}

static int	checkvalidity(char *s, t_map map, int cur)
{
	unsigned int	i;
	static short	flag = 0;

	i = -1;
	while (s[++i])
	{
		if (i > map.wdth + 1)
			return (0);
		if (s[i] == 'x')
			flag += 1;
		if (s[i] != '#' && s[i] != ' ' && s[i] != 'x')
			return (0);
	}
	if ((unsigned int)cur == map.hght && flag != 1)
		return (0);
	return (1);
}

static int	fillmap(t_map *map, int fd)
{
	char			*tmp;
	int				error;
	unsigned int	i;

	i = 0;
	while (((error = (get_next_line(fd, &tmp))) > 0) && ++i)
	{
		if (!checkvalidity(tmp, *map, i))
			return (0);
		map->map[i][0] = '#';
		ft_strcpy(map->map[i] + 1, tmp);
		map->map[i][map->wdth + 1] = '#';
		free(tmp);
		if (i > map->hght)
			return (0);
	}
	ft_strdel(&tmp);
	if (i != map->hght)
		return (0);
	return (1);
}

t_map		*parser(int fd)
{
	t_map			*map;
	char			*str;
	unsigned int	i;

	map = (t_map*)malloc(sizeof(t_map));
	if (!(get_next_line(fd, &str) && (map->wdth = ft_atoi(str))))
		clean_exit(1, &str);
	free(str);
	if (!(get_next_line(fd, &str) && (map->hght = ft_atoi(str))))
		clean_exit(1, &str);
	ft_strdel(&str);
	if (map->wdth == 0 || map->wdth > 50 || map->hght == 0 || map->wdth > 50)
		exit_prog(2);
	if (!(map->map = ((char**)malloc(sizeof(char*) * (map->hght + 2)))))
		exit_prog(1);
	i = -1;
	while (++i < map->hght + 2)
		map->map[i] = ft_strnew(map->wdth + 2);
	ft_memset(map->map[0], '#', map->wdth + 2);
	ft_memset(map->map[map->hght + 1], '#', map->wdth + 2);
	if (!fillmap(map, fd))
		clean_exit(3, map->map);
	return (map);
}
