/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/20 22:14:37 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int	exit_prog(int error)
{
	if (!error)
		ft_putendl("Usage : wolf3d [map]");
	exit(-1);
}

float	get_angle(t_vec a, t_vec b)
{
	float	dot_prod;
	float	magnitude_prod;

	dot_prod = a.x * b.x + a.y * b.y;
	magnitude_prod = sqrt(a.x * a.x + a.y * a.y) * sqrt(b.x * b.x + b.y * b.y);
	return (acos(dot_prod / magnitude_prod));
}

void	calc_height(t_raycast *cast, t_env *env, int col)
{
	int		wall_top;
	int		wall_foot;
	int		perceived;
	int		i;
	perceived = sqrt(env->dir_vec.x * env->dir_vec.x + env->dir_vec.y * env->dir_vec.y) * 800 / cast->dist/*(cast->dist * cos(atan((cast->ray.y - env->dir_vec.y) / env->dir_vec.x)))*/;
	//printf("Perceived : %d Distance : %f\n", perceived, cast->dist);
	wall_top = W_HGHT / 2 - perceived / 2;
	wall_foot = W_HGHT / 2 + perceived / 2;
	i = -1;
	//printf("Top : %d Foot : %d\n", wall_top, wall_foot);
	while (++i < W_HGHT)
	{
		if (i < wall_top)
			putpixel(col, i, -2);
		else if (i <= wall_foot)
			putpixel(col, i, ((cast->wall == 0 ? (cast->step.x + 3) : (cast->step.y + 3)) + cast->wall) * 50);
		else
			putpixel(col, i, -1);
	}
}

void	test_tamere(t_env *env)
{
	t_raycast	cast;
	int			i;
	short		hit;
	t_vec		comp;

	i = -1;
	while (++i < W_WDTH)
	{
		hit = 0;
		cast.dist = 0;
		cast.ray.x = env->dir_vec.x + (env->cam_vec.x * (i - W_WDTH / 2) / (W_WDTH / 2));
		cast.ray.y = env->dir_vec.y + (env->cam_vec.y * (i - W_WDTH / 2) / (W_WDTH / 2));
		cast.dif.x = 1 / fabs(cast.ray.x);
		cast.dif.y = 1 / fabs(cast.ray.y);
		cast.ntile.x = (cast.ray.x < 0 ? env->ppos.x - floor(env->ppos.x) : floor(env->ppos.x + 1) - env->ppos.x) * cast.dif.x;
		cast.ntile.y = (cast.ray.y < 0 ? env->ppos.y - floor(env->ppos.y) : floor(env->ppos.y + 1) - env->ppos.y) * cast.dif.y;
		cast.step.x = cast.ray.x < 0 ? -1 : 1;
		cast.step.y = cast.ray.y < 0 ? -1 : 1;
		cast.map_pos.x = floor(env->ppos.x);
		cast.map_pos.y = floor(env->ppos.y);
		//printf("Next : %f %f\n", cast.ntile.x, cast.ntile.y);
		while(!hit)
		{
			if (cast.ntile.x < cast.ntile.y)
			{
				cast.map_pos.x += cast.step.x;
				comp.x = cast.step.x;
				comp.y = 0;
				cast.dist += (cast.ntile.x / cast.dif.x) / cos(get_angle(cast.ray, comp));
				cast.ntile.x += cast.dif.x;
				cast.wall = 0;
			}
			else
			{
				cast.map_pos.y += cast.step.y;
				comp.x = 0;
				comp.y = cast.step.y;
				cast.dist += (cast.ntile.y / cast.dif.y) / cos(get_angle(cast.ray, comp));
				cast.ntile.y += cast.dif.y;
				cast.wall = 1;
			}
			printf("Distance : %f\n", cast.dist);
			if (env->map[cast.map_pos.x][cast.map_pos.y] == 1)
			{
				hit = 1;
				printf("Wall hit [%d][%d]\n", cast.map_pos.x, cast.map_pos.y);
				calc_height(&cast, env, i);
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
	test_tamere(env);
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
