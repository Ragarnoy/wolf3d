/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:25:06 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/16 20:52:09 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void			setup_sdl(t_env *env)
{
	SDL_Init(SDL_INIT_VIDEO);
	env->win_p = SDL_CreateWindow
		("WOLF3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W_WDTH, W_HGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	env->surf = SDL_GetWindowSurface(env->win_p);
	env->data =(int*)env->surf->pixels;
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
	env->map = malloc(sizeof(int*) * 5);
	while( ++i < 5)
	{
		j = -1;
		env->map[i] = malloc(sizeof(int) * 5);
		while (++j < 5)
			env->map[i][j] = (i % 4 == 0 || j % 4 == 0) ? 1 : 0;
	}
	env->tile_size = 10;
	env->player_pos.x = 20;
	env->player_pos.y = 20;
	env->map_size = 5;
	return (env);
}
