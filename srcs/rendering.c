/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-gac- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:29:16 by tle-gac-          #+#    #+#             */
/*   Updated: 2018/01/29 17:50:10 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	draw_window(t_env *env)
{
	t_win_part		slices[THREAD_NBR];
	SDL_Thread		*threads[THREAD_NBR];
	int				i;
	int				status;

	i = -1;
	while (++i < THREAD_NBR)
	{
		slices[i].a.x = i * W_WDTH / THREAD_NBR;
		slices[i].a.y = 0;
		slices[i].b.x = (i + 1) * W_WDTH / THREAD_NBR;
		slices[i].b.y = W_HGHT;
	}
	i = -1;
	SDL_LockSurface(env->surf);
	while (++i < THREAD_NBR)
		threads[i] = SDL_CreateThread(raycasting, "FredTheThread", &slices[i]);
	i = -1;
	while (++i < THREAD_NBR)
		SDL_WaitThread(threads[i], &status);
	SDL_UnlockSurface(env->surf);
	if (env->flg.minimap)
		minimap(env);
	SDL_UpdateWindowSurface(env->win_p);
}
