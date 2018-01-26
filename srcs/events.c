/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:03:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/26 22:26:29 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	move_dir(int sense, t_env *env)
{
	float	x;
	float	y;
	float	mag;

	mag = sqrt(env->dir_vec.x * env->dir_vec.x + env->dir_vec.y * env->dir_vec.y);
	x = 0.05 * env->dir_vec.x / mag * (env->dir_vec.x == 0 ? 0 : env->dir_vec.x / fabs(env->dir_vec.x)) * (env->dir_vec.x < 0 ? -1 : 1) * sense;
	y = 0.05 * env->dir_vec.y / mag * (env->dir_vec.y == 0 ? 0 : env->dir_vec.y / fabs(env->dir_vec.y)) * (env->dir_vec.y < 0 ? -1 : 1) * sense;
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
	x = 0.05 * env->cam_vec.x / mag * (env->cam_vec.x == 0 ? 0 : env->cam_vec.x / fabs(env->cam_vec.x)) * (env->cam_vec.x < 0 ? -1 : 1) * sense;
	y = 0.05 * env->cam_vec.y / mag * (env->cam_vec.y == 0 ? 0 : env->cam_vec.y / fabs(env->cam_vec.y)) * (env->cam_vec.y < 0 ? -1 : 1) * sense;
	if(env->map.map[(int)(env->ppos.x + x)][(int)(env->ppos.y + y)] != '#')
	{
		env->ppos.x += x;
		env->ppos.y += y;
	}
}

void	rotate(int sense, t_env *env)
{
	float	tmp;

	tmp = env->dir_vec.x * cos(0.05) - env->dir_vec.y * sin(0.05) * sense;
	env->dir_vec.y = env->dir_vec.x * sin(0.05) * sense + env->dir_vec.y * cos(0.05);
	env->dir_vec.x = tmp;
	tmp = env->cam_vec.x * cos(0.05) - env->cam_vec.y * sin(0.05) * sense;
	env->cam_vec.y = env->cam_vec.x * sin(0.05) * sense + env->cam_vec.y * cos(0.05);
	env->cam_vec.x = tmp;
}

void	checkevents(t_env *env)
{
	if (env->flg.mv[0])
		rotate(-1, env);
	if (env->flg.mv[1])
		move_dir(1, env);
	if (env->flg.mv[2])
		move_dir(-1, env);
	if (env->flg.mv[3])
		rotate(1, env);
	if (env->flg.mv[4])
		strafe(-1, env);
	if (env->flg.mv[5])
		strafe(1, env);
	draw_window(env);
}

void	movements(t_env *env, int swtch)
{
SDL_PumpEvents();
	ft_memset(&env->flg.mv, 0, sizeof(int_least8_t) * 6);
	env->flg.mv[4] = (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_LEFT]);
	env->flg.mv[0] = (!env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_LEFT]);
	env->flg.mv[5] = (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_RIGHT]);
	env->flg.mv[3] = (!env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_RIGHT]);
	env->flg.mv[1] = (env->state[SDL_SCANCODE_UP]);
	env->flg.mv[2] = (env->state[SDL_SCANCODE_DOWN]);
	printf("%d: %d %d %d %d %d %d\n", swtch, env->flg.mv[0], env->flg.mv[1], env->flg.mv[2], env->flg.mv[3], env->flg.mv[4], env->flg.mv[5]);
	checkevents(env);
	//redraw
}

void	flags(t_env *env)
{
	if (env->state[SDL_SCANCODE_M] && !env->flg.minimap)
		{
			minimap(env);
			env->flg.minimap = 1;
		}
	else if (env->state[SDL_SCANCODE_M] && env->flg.minimap)
		{
			ft_memset((int*)env->minimap.surf->pixels, 0, (W_WDTH / 4) * 4);
			env->flg.minimap = 0;
		}

}
