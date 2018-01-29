/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:25:06 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/29 21:42:56 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void			setup_sdl(t_env *env)
{
	int		i;

	i = -1;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	env->surtex[0] = SDL_LoadBMP("./tex/colorstone.bmp");
	env->surtex[1] = SDL_LoadBMP("./tex/greystone.bmp");
	env->surtex[2] = SDL_LoadBMP("./tex/stone.bmp");
	env->surtex[3] = SDL_LoadBMP("./tex/mossy.bmp");
	while (++i < TEXNBR)
	{
		if (!env->surtex[i])
			exit_prog(5);
	}
	env->win_p = SDL_CreateWindow("WOLF3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W_WDTH, W_HGHT,
		SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	env->surf = SDL_GetWindowSurface(env->win_p);
	env->data = (Uint32*)env->surf->pixels;
	ft_bzero(env->data, (W_WDTH * W_HGHT) * 4);
	env->state = SDL_GetKeyboardState(NULL);
}

static void			setup_raycast(t_env *env)
{
	unsigned int		i;
	unsigned int		j;

	i = -1;
	while (++i < env->map.hght)
	{
		j = -1;
		while (++j < env->map.wdth)
		{
			if (env->map.map[i][j] == 'x')
			{
				env->ppos[0] = i + 0.5;
				env->ppos[1] = j + 0.5;
			}
		}
	}
	env->tsize = 1.0;
	env->dir_vec[0] = 0.0;
	env->dir_vec[1] = -0.8;
	env->cam_vec[0] = 0.66;
	env->cam_vec[1] = 0.0;
	env->flg.darkness = 1;
}

t_env				*get_env(void)
{
	static t_env	*env = NULL;

	if (env)
		return (env);
	if (!(env = ft_memalloc(sizeof(t_env))))
		exit_prog(0);
	return (env);
}

t_env				*setup_env(t_map lul)
{
	t_env	*env;

	env = get_env();
	setup_sdl(env);
	env->map = lul;
	env->map.wdth += 2;
	env->map.hght += 2;
	setup_raycast(env);
	env->minimap.init = 0;
	env->flg.minimap = 0;
	env->flg.sprint = 1;
	env->lasttick = 0;
	return (env);
}
