/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:25:06 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 15:03:24 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void			setup_sdl(t_env *env)
{
	SDL_Init(SDL_INIT_VIDEO);
	env->win_p = SDL_CreateWindow("WOLF3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W_WDTH, W_HGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	env->surf = SDL_GetWindowSurface(env->win_p);
	env->data = (int*)env->surf->pixels;
	SDL_PumpEvents();
	env->state = SDL_GetKeyboardState(NULL);
	printf("%d:%d, %d %d\n",env->surf->w, env->surf->h, env->surf->pitch, env->surf->format->format);
}

t_env				*get_env(void)
{
	static t_env	*env = NULL;

	if (env)
		return (env);
	if (!(env = malloc(sizeof(t_env))))
		exit_prog(0);
	return (env);
}

t_env				*setup_env(void)
{
	t_env	*env;
	int		i;
	int		j;

	i = -1;
	env = get_env();
	setup_sdl(env);
	env->tsize = 1.0;
	env->ppos.x = 3.5;
	env->ppos.y = 2.8;
	env->map_size.x = 5;
	env->map_size.y = 5;
	env->dir_vec.x = 0.0;
	env->dir_vec.y = -1.0;
	env->cam_vec.x = 0.66;
	env->cam_vec.y = 0.0;
	env->minimap.init = 0;
	env->flg.minimap = 0;
	return (env);
}
