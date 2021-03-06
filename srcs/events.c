/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:03:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/29 20:53:15 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	move_dir(int sense, t_env *env)
{
	float	x;
	float	y;
	float	mag;

	mag = sqrt(env->dir_vec[0] * env->dir_vec[0] +
											env->dir_vec[1] * env->dir_vec[1]);
	x = 0.04 * env->flg.sprint * env->dir_vec[0] / mag * (env->dir_vec[0] ==
			0 ? 0 : env->dir_vec[0] / fabs(env->dir_vec[0])) *
					(env->dir_vec[0] < 0 ? -1 : 1) * sense;
	y = 0.04 * env->flg.sprint * env->dir_vec[1] / mag * (env->dir_vec[1] ==
			0 ? 0 : env->dir_vec[1] / fabs(env->dir_vec[1])) *
					(env->dir_vec[1] < 0 ? -1 : 1) * sense;
	if (env->map.map[(int)(env->ppos[0] + x)][(int)(env->ppos[1] + y)] != '#')
	{
		env->ppos[0] += x;
		env->ppos[1] += y;
	}
}

void	strafe(int sense, t_env *env)
{
	float	x;
	float	y;
	float	mag;

	mag = sqrt(env->cam_vec[0] * env->cam_vec[0] +
											env->cam_vec[1] * env->cam_vec[1]);
	x = 0.04 * env->flg.sprint * env->cam_vec[0] / mag * (env->cam_vec[0] ==
			0 ? 0 : env->cam_vec[0] / fabs(env->cam_vec[0])) *
					(env->cam_vec[0] < 0 ? -1 : 1) * sense;
	y = 0.04 * env->flg.sprint * env->cam_vec[1] / mag * (env->cam_vec[1] ==
			0 ? 0 : env->cam_vec[1] / fabs(env->cam_vec[1])) *
					(env->cam_vec[1] < 0 ? -1 : 1) * sense;
	if (env->map.map[(int)(env->ppos[0] + x)][(int)(env->ppos[1] + y)] != '#')
	{
		env->ppos[0] += x;
		env->ppos[1] += y;
	}
}

void	rotate(int sense, t_env *env)
{
	float	tmp;

	tmp = env->dir_vec[0] * cos(0.03) - env->dir_vec[1] * sin(0.03) * sense;
	env->dir_vec[1] = env->dir_vec[0] * sin(0.03) * sense + env->dir_vec[1] * \
																	cos(0.03);
	env->dir_vec[0] = tmp;
	tmp = env->cam_vec[0] * cos(0.03) - env->cam_vec[1] * sin(0.03) * sense;
	env->cam_vec[1] = env->cam_vec[0] * sin(0.03) * sense + env->cam_vec[1] * \
																	cos(0.03);
	env->cam_vec[0] = tmp;
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
	while (env->lasttick + (1000 / 50) > SDL_GetTicks())
		;
	env->lasttick = SDL_GetTicks();
	draw_window(env);
}

void	flags(t_env *env, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_M)
		env->flg.minimap = !env->flg.minimap;
	if (event.key.keysym.scancode == SDL_SCANCODE_D)
		env->flg.darkness = !env->flg.darkness;
	if (env->flg.sprint == 1 && event.key.keysym.scancode ==
															SDL_SCANCODE_S)
		env->flg.sprint = 2;
	else if (env->flg.sprint == 2 && event.key.keysym.scancode
															== SDL_SCANCODE_W)
		env->flg.sprint = 1;
}
