/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:06:22 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/16 20:53:50 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static int		checkvalidity(char **s, int hght, int wdth)
{
	if (wdth < 0 || hght < 0)
		return (0);
	while (hght-- != 0)
	{
		while (wdth-- != 0)
		{
			if (
		}

	return (1);
}

static int	**fillmap(char **s, int c_size, int l_size)
{
	int		l;
	int		c;
	char	**tmp;
	t_point	**ret;

	c = c_size;
	if (!(ret = (t_point**)malloc(sizeof(t_point*) * l_size)))
		usage(2, NULL);
	l = -1;
	while (++l < l_size)
	{
		c = -1;
		if (!(ret[l] = ((t_point*)malloc(sizeof(t_point) * c_size))))
			usage(2, NULL);
		tmp = ft_strsplit(s[l], ' ');
		while (++c < c_size && tmp[c])
		{
			(ret[l][c]).alt = ft_atoi(tmp[c]);
			ft_strdel(tmp + c);
		}
		free(tmp);
	}
	return (ret);
}

t_map			**parser(int fd, int *wdth, int *hght)
{
	char	**s;
	int		error;
	t_point	**ret;

	*wdth = -1;
	*hght = -1;
	if (!(s = (char**)ft_memalloc(sizeof(char *) * 25)))
		exit_prog(2);
	while ((((error = (get_next_line(fd, &(s[*++hght])))) && l < MAX_S)))
	{
		if (error == -1)
			exit_prog(2);
		if (c == -1)
			c = ft_countwords(s[l], ' ');
		else if ((int)ft_countwords(s[l], ' ') != c || c < 1)
			exit_prog(3);
	}
	if (!(setmaxsize(s, wdth, hght)))
		exit_prog(3);
	ret = fillmap(s, c, l);
	return (ret);
}
