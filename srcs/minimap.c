/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:43:02 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/22 19:30:04 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	sqr(t_env *env, int sow, INTL x, INTL y)
{
	int i = 0;
	int j = 0;
	int scale;

	scale = env->map.hght + 2 / env->minimap.dst.w;
	while (i < scale)
	{
		while (j < scale)
		{
			((int*)env->minimap.surf->pixels)[(x * i) + ((j * y) * env->minimap.dst.w)] = sow;
			j++;
		}
		i++;
	}
}

static void	draw(t_env *env)
{
	INTL	x;
	INTL	y;

	x = 0;
	y = 0;
	while (y < env->map.hght + 2)
	{
		while (x < env->map.wdth + 2)
		{
			if (env->map.map[y][x] == '#')
				sqr(env, 0, x, y);
			if (env->flg.minimap)
				minimap(env);
			else if (env->map.map[y][x] == ' ')
				sqr(env, 0xFFFFFF, x, y);
			x++;
		}
		y++;
	}
}

static void	init_minimap(t_env *env)
{
	env->minimap.surf = SDL_CreateRGBSurfaceWithFormat(0, 4 / W_WDTH, 4 / W_HGHT, 32, env->surf->format->format);
	env->minimap.dst.x = W_WDTH - (W_HGHT / 4);
	env->minimap.dst.y = 0;
	env->minimap.dst.w = (W_HGHT / 4);
	env->minimap.dst.h = (W_HGHT / 4);
}

void	minimap(t_env *env)
{
	if (!env->minimap.init)
		init_minimap(env);
	draw(env);
	SDL_BlitSurface(env->minimap.surf, 0, env->surf, &env->minimap.dst);
}
