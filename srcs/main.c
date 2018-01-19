/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/19 20:09:33 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int	exit_prog(int error)
{
	if (!error)
		ft_putendl("Usage : wolf3d [map]");
	exit(-1);
}

void	height_calc(t_raycast *cast, int col)
{
	int		i;
	t_pnt	pix;

	i = -1;
	pix.x = col;
	while (++i < W_HGHT)
	{
		pix.y = i;
		if (i < -(W_HGHT / cast->dist) / 2 + W_HGHT / 2)
			putpixel(pix, 0);
		else if (i < (W_HGHT / cast->dist) / 2 + W_HGHT / 2)
			putpixel (pix, (cast->wall + (cast->wall == 1 ? abs(cast->steps.    x) + 1: abs(cast->steps.y) + 1)) * 50);
		else
			putpixel (pix, 0);
	}
}

void	raycasting(t_env *env)
{
	t_raycast	cast;
	int			i;
	//int			j;
	short		hit;
	//t_pnt		pix;

	i = -1;
	while (++i < W_WDTH)
	{
		//pix.x = i;
		hit = 0;
		cast.ray.x = env->dir_vec.x + env->cam_vec.x * ((i - W_WDTH / 2) / (W_WDTH / 2));
		cast.ray.y = env->dir_vec.y + env->cam_vec.y * ((i - W_WDTH / 2) / (W_WDTH / 2));
		//printf("Ray : %f %f\n", cast.ray.x, cast.ray.y);
		cast.map_pos.x = env->ppos.x / env->tsize;
		cast.map_pos.y = env->ppos.y / env->tsize;
		//printf("Map pos : %d %d\n", cast.map_pos.x, cast.map_pos.y);
		cast.ntile.x = cast.ray.x < 0 ? (env->ppos.x % env->tsize) * fabs(1 / cast.ray.x) : (env->tsize - env->ppos.x % env->tsize) * fabs(10 / cast.ray.x);
		cast.ntile.y = cast.ray.y < 0 ? (env->ppos.y % env->tsize) * fabs(1 / cast.ray.y) : (env->tsize - env->ppos.y % env->tsize) * fabs(10 / cast.ray.y);
		//printf("Next tile : %f %f\n", cast.ntile.x, cast.ntile.y);
		cast.steps.x = cast.ray.x < 0 ? -1 : 1;
		cast.steps.y = cast.ray.y < 0 ? -1 : 1;
		//printf("Steps : %d %d\n", cast.steps.x, cast.steps.y);
		cast.wall = 0;
		//cast struct initialization DONE
		while(!hit)
		{
			if (cast.ntile.x < cast.ntile.y)
			{
				cast.ntile.x += fabs(1 / cast.ray.x);
				cast.map_pos.x += cast.steps.x;
				cast.wall = 0;
				cast.dist = (cast.map_pos.x - env->ppos.x + (1 - cast.steps.x) / 2) / cast.ray.x;
			}
			else
			{
				cast.ntile.y += fabs(cast.ray.y);
				cast.map_pos.y += cast.steps.y;
				cast.wall = 1;
				cast.dist = (cast.map_pos.y - env->ppos.y + (1 - cast.steps.y) / 2) / cast.ray.y;
			}
			printf("Distance to wall : %f\n", cast.dist);
			//printf("Ray at map [%d][%d]\n", cast.map_pos.x, cast.map_pos.y);
			if (env->map[cast.map_pos.x][cast.map_pos.y] == 1)
			{
				//j = -1;
				hit = 1;
				printf("Hit at map[%d][%d]\n", cast.map_pos.x, cast.map_pos.y);
				/*while (++j < W_HGHT)
				{
					pix.y = j;
					putpixel(pix, (cast.wall + (cast.wall == 1 ? abs(cast.steps.x) + 1: abs(cast.steps.y) + 1)) * 50);
				}*/
				cast.dist = cast.wall == 0 ? (cast.map_pos.x - env->ppos.x + (1 - cast.steps.x) / 2) / cast.ray.x : (cast.map_pos.y - env->ppos.y + (1 - cast.steps.y) / 2) / cast.ray.y;
				height_calc(&cast, i);
			}
		}
	}
}

int	main(void)
{
	t_env		*env;
	int			running = 1;
	SDL_Event	event;

	env = setup_env();
	raycasting(env);
	SDL_UpdateWindowSurface(env->win_p);
	while (running)
		while(SDL_PollEvent(&event))
			if((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				running = 0;
	SDL_DestroyWindow(env->win_p);
	SDL_Quit();
	return (0);
}

/*
 * ligne 29 pour maj la fenetre
 * Sinon pour l'instant la fenetre va etre vide, normal
 * voila
*/
