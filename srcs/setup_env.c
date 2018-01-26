/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:25:06 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/26 22:28:45 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void			setup_sdl(t_env *env)
{
	SDL_Init(SDL_INIT_VIDEO);
	env->win_p = SDL_CreateWindow("WOLF3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		W_WDTH, W_HGHT,
		0);
	env->surf = SDL_GetWindowSurface(env->win_p);
	env->data = (int*)env->surf->pixels;
	SDL_PumpEvents();
	env->state = SDL_GetKeyboardState(NULL);
	env->surtex[0] = SDL_LoadBMP("./tex/colorstone.bmp");
	env->surtex[1] = SDL_LoadBMP("./tex/greystone.bmp");
	env->surtex[2] = SDL_LoadBMP("./tex/mossy.bmp");
	env->surtex[3] = SDL_LoadBMP("./tex/wood.bmp");
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

t_env				*setup_env(t_map lul)
{
	t_env				*env;
	unsigned int		i;
	unsigned int		j;

	i = -1;
	j = -1;
	env = get_env();
	setup_sdl(env);
	env->map = lul;
	env->map.wdth += 2;
	env->map.hght += 2;
	while (++i < env->map.hght)
	{
		while (++j < env->map.wdth)
			if (env->map.map[i][j] == 'x')
			{
				env->ppos.x = j + 0.5;
				env->ppos.y = i + 0.5;
			}
		j = -1;
	}
	env->tsize = 1.0;
	env->dir_vec.x = 0.0;
	env->dir_vec.y = -0.8;
	env->cam_vec.x = 0.66;
	env->cam_vec.y = 0.0;
	env->minimap.init = 0;
	ft_bzero(&env->flg, sizeof(t_flags));
	return (env);
}
