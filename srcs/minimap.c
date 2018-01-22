/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:43:02 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/22 18:01:36 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	sqr(t_env *env, int sow, INTL x, INTL y)
{
	int i;
	t_pnt scale;

	scale.x = env->minimap.dst.w;
	scale.y = env->minimap.dst.y + ((env->minimap.dst.y - env->minimap.dst.h) * y);
}

static void	draw(t_env *env)
{
	INTL	i;
	INTL	j;

	i = 0;
	j = 0;
	while (i < env->map.hght + 2)
	{
		while (j < env->map.wdth + 2)
		{
			
		}
		i++;
	}
}

static void	init_minimap(t_env *env)
{
	env->minimap.surf = SDL_CreateRGBSurfaceWithFormat(0, 4 / W_WDTH, 4 / W_HGHT, 32, env->surf->format->format);
	env->minimap.dst.x = W_WDTH - (W_WDTH / 4);
	env->minimap.dst.y = W_HGHT - (W_HGHT / 4);
	env->minimap.dst.w = (W_WDTH / 4);
	env->minimap.dst.h = (W_HGHT / 4);
}

void	minimap(t_env *env)
{
	if (!env->minimap.surf)
		init_minimap(env);
}
