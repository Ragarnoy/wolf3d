/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:25:06 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/16 17:56:39 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void			setup_sdl(t_env *env)
{
	SDL_Surface	*surface;
	SDL_Init(SDL_INIT_VIDEO);
	env->win_p = SDL_CreateWindow
		("WOLF3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W_WDTH, W_HGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	surface = SDL_GetWindowSurface(env->win_p);
	env->img.data =(int*)surface->pixels;
	env->img.l_size = surface->pitch;
	env->img.bpp = surface->format->BitsPerPixel;
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

	env = get_env();
	setup_sdl(env);
	return (env);
}