/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-gac- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:29:16 by tle-gac-          #+#    #+#             */
/*   Updated: 2018/01/28 17:43:38 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

/*void	homebrew_blit(t_env *env)
{
	int		*tmp;
	int		i = 0;
	int		j = 0;

	while (i < 64)
	{
		while (j < 64)
		{
			tmp = (int *)&((char*)env->surtex[0]->pixels)[(3 * i) * 64 + (3 * j)];
			env->data[i * W_WDTH + j] = *tmp;//255 << 24 | (tmp[1] << 16) | (tmp[2] << 8) | tmp[3];
			j++;
		}
		i++;
		j = 0;
	}
}*/

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
	while (++i < THREAD_NBR)
		threads[i] = SDL_CreateThread(raycasting, "FredTheThread", &slices[i]);
	i = -1;
	while (++i < THREAD_NBR)
		SDL_WaitThread(threads[i], &status);
	if (env->flg.minimap)
		minimap(env);
	SDL_UpdateWindowSurface(env->win_p);
}
