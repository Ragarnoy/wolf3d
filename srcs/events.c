/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:03:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/28 17:37:00 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	move_dir(int sense, t_env *env)
{
	float	x;
	float	y;
	float	mag;

	mag = sqrt(env->dir_vec.x * env->dir_vec.x +
											env->dir_vec.y * env->dir_vec.y);
	x = 0.05 * env->dir_vec.x / mag * (env->dir_vec.x == 0 ? 0 : env->dir_vec.x
		/ fabs(env->dir_vec.x)) * (env->dir_vec.x < 0 ? -1 : 1) * sense;
	y = 0.05 * env->dir_vec.y / mag * (env->dir_vec.y == 0 ? 0 : env->dir_vec.y
		/ fabs(env->dir_vec.y)) * (env->dir_vec.y < 0 ? -1 : 1) * sense;
	if (env->map.map[(int)(env->ppos.x + x)][(int)(env->ppos.y + y)] != '#')
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

	mag = sqrt(env->cam_vec.x * env->cam_vec.x +
											env->cam_vec.y * env->cam_vec.y);
	x = 0.05 * env->cam_vec.x / mag * (env->cam_vec.x == 0 ? 0 : env->cam_vec.x
			/ fabs(env->cam_vec.x)) * (env->cam_vec.x < 0 ? -1 : 1) * sense;
	y = 0.05 * env->cam_vec.y / mag * (env->cam_vec.y == 0 ? 0 : env->cam_vec.y
			/ fabs(env->cam_vec.y)) * (env->cam_vec.y < 0 ? -1 : 1) * sense;
	if (env->map.map[(int)(env->ppos.x + x)][(int)(env->ppos.y + y)] != '#')
	{
		env->ppos.x += x;
		env->ppos.y += y;
	}
}

void	rotate(int sense, t_env *env)
{
	float	tmp;

	tmp = env->dir_vec.x * cos(0.04) - env->dir_vec.y * sin(0.04) * sense;
	env->dir_vec.y = env->dir_vec.x * sin(0.04) * sense +
													env->dir_vec.y * cos(0.04);
	env->dir_vec.x = tmp;
	tmp = env->cam_vec.x * cos(0.04) - env->cam_vec.y * sin(0.04) * sense;
	env->cam_vec.y = env->cam_vec.x * sin(0.04) * sense +
													env->cam_vec.y * cos(0.04);
	env->cam_vec.x = tmp;
}

void	movements(t_env *env)
{
	if (env->state[SDL_SCANCODE_UP])
		move_dir(1, env);
	if (env->state[SDL_SCANCODE_DOWN])
		move_dir(-1, env);
	if (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_RIGHT])
		strafe(-1, env);
	else if (env->state[SDL_SCANCODE_RIGHT])
		rotate(-1, env);
	if (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_LEFT])
		strafe(1, env);
	else if (env->state[SDL_SCANCODE_LEFT])
		rotate(1, env);
	draw_window(env);
}

void	flags(t_env *env, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_M)
		env->flg.minimap = !env->flg.minimap;
}
