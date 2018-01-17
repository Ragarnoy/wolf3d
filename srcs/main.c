/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/17 23:01:58 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int	exit_prog(int error)
{
	if (!error)
		ft_putendl("Usage : wolf3d [map]");
	exit(-1);
}

void	test_tamere(t_env *env)
{
	t_raycast	cast;
	int			i;
	short		hit;

	i = -1;
	while (++i < W_WDTH)
	{
		hit = 0;
		cast.ray.x = env->dir_vec.x + env->cam_vec.x * ((i - W_WDTH / 2) / (W_WDTH / 2));
		cast.ray.y = env->dir_vec.y + env->cam_vec.y * ((i - W_WDTH / 2) / (W_WDTH / 2));
		cast.map_pos.x = env->ppos.x / env->tsize;
		cast.map_pos.y = env->ppos.y / env->tsize;
		cast.ntile.x = cast.ray.x < 0 ? (env->ppos.x % env->tsize) * fabs(1 / cast.ray.x) : (env->tsize - env->ppos.x % env->tsize) * fabs(1 / cast.ray.x);
		cast.ntile.y = cast.ray.y < 0 ? (env->ppos.y % env->tsize) * fabs(1 / cast.ray.y) : (env->tsize - env->ppos.y % env->tsize) * fabs(1/ cast.ray.y);
		cast.steps.x = cast.ray.x < 0 ? -1 : 1;
		cast.steps.y = cast.ray.y < 0 ? -1 : 1;
		cast.wall = 0;
		//cast struct initialization DONE
		while(!hit)
		{
			if (cast.ntile.x < cast.ntile.y)
			{
				cast.ntile.x += 1 / cast.ray.x;
				cast.map_pos.x += cast.steps.x;
				cast.wall = 1;
			}
			else
			{
				cast.ntile.y += cast.ray.y;
				cast.map_pos.y += cast.steps.y;
				cast.wall = -1;
			}
			if (env->map[cast.map_pos.x][cast.map_pos.y] == 1)
			{
				hit = 1;
				printf("Hit at map[%d][%d]\n", cast.map_pos.x, cast.map_pos.y);
			}
		}
	}
}

int	main(void)
{
	t_env		*env;
	//int			running = 1;
	//SDL_Event	event;

	env = setup_env();
	test_tamere(env);
	/*SDL_UpdateWindowSurface(env->win_p);
	while (running)
		while(SDL_PollEvent(&event))
			if((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				running = 0;
	SDL_DestroyWindow(env->win_p);
	SDL_Quit();*/
	return (0);
}

/*
 * ligne 29 pour maj la fenetre
 * Sinon pour l'instant la fenetre va etre vide, normal
 * voila
*/
