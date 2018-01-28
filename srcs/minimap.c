/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:43:02 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/28 17:42:45 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	sqr(t_env *env, int c, INTL x, INTL y)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	scale;
	int				*data;

	i = 0;
	data = (int*)env->minimap.surf->pixels;
	scale = env->minimap.dst.w / (env->map.hght);
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			data[(x * scale + i) + ((y * scale + j) * env->minimap.dst.w)] = c;
			j++;
		}
		i++;
	}
}

static void	draw(t_env *env)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < env->map.hght)
	{
		x = 0;
		while (x < env->map.wdth)
		{
			if (env->map.map[y][x] == '#')
				sqr(env, 0xFFFF0000, x, y);
			else if (env->map.map[y][x] == ' ' || env->map.map[y][x] == 'x')
				sqr(env, 0xFF000000, x, y);
			x++;
		}
		y++;
	}
}

static void	init_minimap(t_env *env)
{
	env->minimap.surf = SDL_CreateRGBSurfaceWithFormat(0, W_WDTH / 8,
				W_WDTH / 8, 32, env->surf->format->format);
	env->minimap.dst.x = W_WDTH - (W_WDTH / 8) + 4;
	env->minimap.dst.y = 0;
	env->minimap.dst.w = (W_WDTH / 8);
	env->minimap.dst.h = (W_WDTH / 8);
	draw(env);
	env->minimap.init = 1;
}

void		minimap(t_env *env)
{
	if (env->minimap.init == 0)
		init_minimap(env);
	SDL_BlitScaled(env->minimap.surf, 0, env->surf, &env->minimap.dst);
	SDL_UpdateWindowSurface(env->win_p);
}
