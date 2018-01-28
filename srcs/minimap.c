/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:43:02 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/28 20:47:00 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	sqr(t_env *env, int c, INTL x, INTL y)
{
	t_pnt			pt;
	int				scl;
	int				*data;

	pt.y = 0;
	data = (int*)env->minimap.surf->pixels;
	if (env->map.hght > env->map.wdth)
		scl = env->minimap.dst.w / (env->map.hght);
	else
		scl = env->minimap.dst.w / (env->map.wdth);
	while (pt.y < scl)
	{
		pt.x = 0;
		while (pt.x < scl)
		{
			data[(x * scl + pt.x) + ((y * scl + pt.y)
					* env->minimap.dst.w)] = c;
			pt.x++;
		}
		pt.y++;
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
	env->minimap.dst.y = 0;
	env->minimap.dst.x = W_WDTH - (W_WDTH / 8);
	env->minimap.dst.w = (W_WDTH / 8);
	env->minimap.dst.h = (W_WDTH / 8);
	if (env->map.hght > env->map.wdth)
		env->minimap.dst.x += W_WDTH / 8 - ((env->minimap.dst.w /
											(env->map.hght)) * env->map.wdth);
	else
		env->minimap.dst.x += (W_WDTH / 8) - ((env->minimap.dst.w /
											(env->map.wdth)) * env->map.wdth);
	draw(env);
	env->minimap.init = 1;
}

void		minimap(t_env *env)
{
	if (env->minimap.init == 0)
		init_minimap(env);
	SDL_BlitSurface(env->minimap.surf, 0, env->surf, &env->minimap.dst);
	SDL_UpdateWindowSurface(env->win_p);
}
