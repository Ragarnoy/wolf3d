/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-gac- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:29:02 by tle-gac-          #+#    #+#             */
/*   Updated: 2018/01/29 20:01:13 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

float	get_angle(double *a, double *b)
{
	float	dot_prod;
	float	magnitude_prod;

	dot_prod = a[0] * b[0] + a[1] * b[1];
	magnitude_prod = sqrt(a[0] * a[0] + a[1] * a[1]) * sqrt(b[0] * b[0] +\
			b[1] * b[1]);
	return (acos(dot_prod / magnitude_prod));
}

t_wall	calc_height(t_raycast *cast, t_env *env)
{
	t_wall	w;
	float	zekflop;

	w.perceived = sqrt(env->dir_vec[0] * env->dir_vec[0] + env->dir_vec[1] * \
			env->dir_vec[1]) * W_HGHT / (cast->dist * cos(get_angle(cast->ray, \
			env->dir_vec)));
	if (cast->wall == 0)
	{
		if (cast->ray[1] == 0)
			cast->relative_pos = modff(env->ppos[1], &zekflop);
		else
			cast->relative_pos = cast->step[1] == 1 ? 1 - (cast->ntile[1] / \
					cast->dif[1]) : cast->ntile[1] / cast->dif[1];
	}
	else
	{
		if (cast->ray[0] == 0)
			cast->relative_pos = modff(env->ppos[0], &zekflop);
		else
			cast->relative_pos = cast->step[0] == 1 ? 1 - (cast->ntile[0] / \
					cast->dif[0]) : cast->ntile[0] / cast->dif[0];
	}
	w.top = W_HGHT / 2.0 - w.perceived / 2.0;
	w.foot = W_HGHT / 2.0 + w.perceived / 2.0;
	return (w);
}

int		draw_pix_column(t_raycast *cast, t_env *env, int col)
{
	t_wall		w;
	int			i;

	w = calc_height(cast, env);
	i = 0;
	while (i < w.top)
		env->data[i++ * W_WDTH + col] = 0;
	while (i < w.foot && i < W_HGHT)
	{
		if (cast->dist > 3.0 && env->flg.darkness)
			env->data[i * W_WDTH + col] = 0;
		else
			env->data[i * W_WDTH + col] = *(uint32_t*)((env->surtex[1 + \
				cast->wall + (cast->wall == 0 ? cast->step[0] : \
				cast->step[1])]->pixels) + ((3 * (int)(63 * \
				cast->relative_pos)) + 64 * (3 * (63 * (i - w.top) /\
				w.perceived))));
		i++;
	}
	while (i < W_HGHT)
		env->data[i++ * W_WDTH + col] = 0;
	return (1);
}

void	find_wall(t_raycast *cast, t_env *env, int i)
{
	short	hit;
	double	comp[2];

	hit = 0;
	while (!hit)
	{
		if (cast->ntile[0] < cast->ntile[1])
			cast->wall = 0;
		else
			cast->wall = 1;
		cast->map_pos[cast->wall] += cast->step[cast->wall];
		comp[abs(cast->wall - 1)] = 0;
		comp[cast->wall] = cast->step[cast->wall];
		cast->dist += (cast->ntile[cast->wall] / cast->dif[cast->wall]) /\
					cos(get_angle(cast->ray, comp));
		cast->ntile[abs(cast->wall - 1)] -= cast->ntile[cast->wall];
		cast->ntile[cast->wall] = cast->dif[cast->wall];
		if (env->map.map[cast->map_pos[0]][cast->map_pos[1]] == '#')
			hit = draw_pix_column(cast, env, W_WDTH - i - 1);
	}
}

int		raycasting(void *tmp)
{
	t_raycast	cast;
	int			i;
	int			j;
	t_env		*env;
	t_win_part	*part;

	env = get_env();
	part = (t_win_part*)tmp;
	i = part->a.x - 1;
	while (++i < part->b.x && !(cast.dist = 0))
	{
		j = -1;
		while (++j < 2)
		{
			cast.ray[j] = env->dir_vec[j] + (env->cam_vec[j] * \
					(i - W_WDTH / 2) / (W_WDTH / 2));
			cast.dif[j] = 1 / fabs(cast.ray[j]);
			cast.ntile[j] = (cast.ray[j] < 0 ? env->ppos[j] - floor(env->ppos\
				[j]) : floor(env->ppos[j] + 1) - env->ppos[j]) * cast.dif[j];
			cast.step[j] = cast.ray[j] < 0 ? -1 : 1;
			cast.map_pos[j] = floor(env->ppos[j]);
		}
		find_wall(&cast, env, i);
	}
	return (1);
}
