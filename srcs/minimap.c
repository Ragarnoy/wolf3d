/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:43:02 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 18:34:34 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	sqr(t_env *env, int c, INTL x, INTL y)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int scale;
	int			*data;

	data = (int*)env->minimap.surf->pixels;
	scale = env->minimap.dst.w / (env->map.hght);
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			data[(x * scale + i) + ((y * scale + j) * env->minimap.dst.w)] = c;
			//printf("%#010x at %d\n",c, (x * scale + i) + ((y * scale + j) * env->minimap.dst.w));
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
				sqr(env, 0x00FF0000, x, y);
			else if (env->map.map[y][x] == ' ' || env->map.map[y][x] == 'x')
				sqr(env, 0x00000000, x, y);
			x++;
		}
		y++;
	}
}

static void	init_minimap(t_env *env)
{
	env->minimap.surf = SDL_CreateRGBSurfaceWithFormat(0, W_WDTH / 8, W_HGHT / 8, 32, env->surf->format->format);
	env->minimap.dst.x = W_WDTH - (W_HGHT / 8);
	env->minimap.dst.y = 0;
	env->minimap.dst.w = (W_HGHT / 8);
	env->minimap.dst.h = (W_HGHT / 8);
	printf("%d:%d, %d %d\n",env->minimap.surf->w, env->minimap.surf->h, env->minimap.surf->pitch, env->minimap.surf->format->format);
	env->minimap.init = 1;
}

void	minimap(t_env *env)
{
	if (env->minimap.init == 0)
		init_minimap(env);
	draw(env);
	SDL_BlitSurface(env->minimap.surf, 0, env->surf, &env->minimap.dst);
	SDL_UpdateWindowSurface(env->win_p);
}
