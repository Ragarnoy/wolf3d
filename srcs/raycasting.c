/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-gac- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:29:02 by tle-gac-          #+#    #+#             */
/*   Updated: 2018/01/26 19:02:42 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

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
	float	zekflop;

	perceived = sqrt(env->dir_vec.x * env->dir_vec.x + env->dir_vec.y * env->dir_vec.y) * W_HGHT / (cast->dist * cos(get_angle(cast->ray, env->dir_vec)));
	//printf("Perceived : %d Distance : %f\n", perceived, cast->dist);
	if (cast->wall == 0)
	{
		if (cast->ray.y == 0)
			cast->relative_pos = modff(env->ppos.y, &zekflop);
		else
			cast->relative_pos = cast->step.y == 1 ? 1 - (cast->ntile.y / cast->dif.y) : cast->ntile.y / cast->dif.y;
	}
	else
	{
		if (cast->ray.x == 0)
			cast->relative_pos = modff(env->ppos.x, &zekflop);
		else
			cast->relative_pos = cast->step.x == 1 ? 1 - (cast->ntile.x / cast->dif.x) : cast->ntile.x / cast->dif.x;
	}
	if (cast->ray.x == 0 || cast->ray.y == 0)
		//printf("Relative pos = %f / %f = %f\n", cast->wall == 0 ? cast->ntile.y : cast->ntile.x, cast->wall == 0 ? cast->dif.y : cast->dif.x, cast->relative_pos);
	wall_top = W_HGHT / 2 - perceived / 2;
	wall_foot = W_HGHT / 2 + perceived / 2;
	i = -1;
	//printf("Top : %d Foot : %d\n", wall_top, wall_foot);
	while (++i < W_HGHT)
	{
		if (i < wall_top)
			putpixel(col, i, -2);
		else if (i <= wall_foot)
		{
			//putpixel(col, i, get_texture(((cast->wall == 0 ? (cast->step.x + 3) : (cast->step.y + 3)) + cast->wall) * 50, env, cast));
			env->data[i * W_WDTH + col] = ((int*)env->surtex[0]->pixels)[(int)(400 * cast->relative_pos) + 400 * (int)(400 / perceived * (i - wall_top))];
		}
		else
			putpixel(col, i, -1);
	}
}

int		raycasting(void *tmp)
{
	t_raycast	cast;
	int			i;
	short		hit;
	t_vec		comp;
	t_env		*env;
	t_win_part	*part;

	env = get_env();
	part = (t_win_part*)tmp;
	i = part->a.x - 1;
	while (++i < part->b.x)
	{
		hit = 0;
		cast.dist = 0;
		cast.ray.x = env->dir_vec.x + (env->cam_vec.x * (i - W_WDTH / 2) / (W_WDTH / 2));
		cast.ray.y = env->dir_vec.y + (env->cam_vec.y * (i - W_WDTH / 2) / (W_WDTH / 2));
		//printf("Ray number %d : %f %f\n", i, cast.ray.x, cast.ray.y);
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
				cast.ntile.y -= cast.ntile.x;
				cast.ntile.x = cast.dif.x;
				cast.wall = 0;
			}
			else
			{
				cast.map_pos.y += cast.step.y;
				comp.x = 0;
				comp.y = cast.step.y;
				cast.dist += (cast.ntile.y / cast.dif.y) / cos(get_angle(cast.ray, comp));
				cast.ntile.x -=  cast.ntile.y;
				cast.ntile.y = cast.dif.y;
				cast.wall = 1;
			}
			//printf("Distance : %f\n", cast.dist);
			if (env->map.map[cast.map_pos.x][cast.map_pos.y] == '#')
			{
				hit = 1;
				calc_height(&cast, env, i);
			}
		}
	}
	return (1);
}
