/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:03:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 18:34:56 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	movements(t_env *env)
{
	if (env->state[SDL_SCANCODE_UP])
		printf("up !\n");
	if (env->state[SDL_SCANCODE_DOWN])
		printf("down !\n");
	if (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_LEFT])
		printf("strafe left !\n");
	else if (env->state[SDL_SCANCODE_LEFT])
		printf("left !\n");
	if (env->state[SDL_SCANCODE_X] && env->state[SDL_SCANCODE_RIGHT])
		printf("strafe right !\n");
	else if (env->state[SDL_SCANCODE_RIGHT])
		printf("right !\n");
	//redraw
}

void	flags(t_env *env)
{
	if (env->state[SDL_SCANCODE_P])
	{
		env->flg.minimap = !env->flg.minimap;
/*		if (!env->flg.minimap)
			//redraw?
			;*/
	}
}
