/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:03:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 20:57:53 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	move_dir(int sense, t_env *env)
{
	float	x;
	float	y;
	float	mag;

	mag = sqrt(env->dir_vec.x * env->dir_vec.x + env->dir_vec.y * env->dir_vec.y);
	x = 0.05 * env->dir_vec.x / mag * (env->dir_vec.x == 0 ? 0 : env->dir_vec.x / fabs(env->dir_vec.x)) * sense;
	y = 0.05 * env->dir_vec.y / mag * (env->dir_vec.y == 0 ? 0 : env->dir_vec.y / fabs(env->dir_vec.y)) * sense;
	printf("New pos : %f %f\n", env->ppos.x + x, env->ppos.y + y);
	if(env->map.map[(int)(env->ppos.x + x)][(int)(env->ppos.y + y)] != '#')
	{
		env->ppos.x += x;
		env->ppos.y += y;
	}
}

void	strafe(int sense, t_env *env)
{
	float	x;
	float	y;
	float	mag;

	mag = sqrt(env->cam_vec.x * env->cam_vec.x + env->cam_vec.y * env->cam_vec.y);
	x = 0.05 * env->cam_vec.x / mag * (env->cam_vec.x == 0 ? 0 : env->cam_vec.x / fabs(env->cam_vec.x)) * sense;
	y = 0.05 * env->cam_vec.y / mag * (env->cam_vec.y == 0 ? 0 : env->cam_vec.y / fabs(env->cam_vec.y)) * sense;
	printf("New pos : %f %f\n", env->ppos.x + x, env->ppos.y + y);
	if(env->map.map[(int)(env->ppos.x + x)][(int)(env->ppos.y + y)] != '#')
	{
		env->ppos.x += x;
		env->ppos.y += y;
	}
	
}

void	movements(t_env *env)
{
	if (env->state[SDL_SCANCODE_UP])
		move_dir(-1, env);
	if (env->state[SDL_SCANCODE_DOWN])
		move_dir(1, env);
	if (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_LEFT])
		strafe(-1, env);
	else if (env->state[SDL_SCANCODE_LEFT])
		printf("left !\n");
	if (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_RIGHT])
		strafe(1, env);
	else if (env->state[SDL_SCANCODE_RIGHT])
		printf("right !\n");
	raycasting(env);
	SDL_UpdateWindowSurface(env->win_p);
	//redraw
}

void	flags(t_env *env)
{
	if (env->state[SDL_SCANCODE_P])
	{
		env->flg.minimap = !env->flg.minimap;
		if (!env->flg.minimap)
			//redraw?
			;
	}
	SDL_UpdateWindowSurface(env->win_p);
}
