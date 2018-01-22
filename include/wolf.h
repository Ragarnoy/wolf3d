/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:26:50 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/22 18:14:05 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define MAX_INT 2147483647
# define intf uint_fast8_t
# define intl uint_least8_t
# define W_WDTH 800
# define W_HGHT 800
# define WALL 35

# include "../libft/libft.h"
# include <SDL.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>

typedef struct			s_vec
{
	double				x;
	double				y;
}						t_vec;

typedef struct			s_pnt
{
	int					x;
	int					y;
}						t_pnt;

typedef struct			s_raycast
{
	t_vec				ntile;
	t_vec				ray;
	t_pnt				step;
	t_pnt				map_pos;
	t_vec				dif;
	float				dist;
	short				wall;
}						t_raycast;

typedef struct			s_env
{
	int					*data;
	SDL_Window			*win_p;
	SDL_Event			event;
	SDL_Surface			*surf;
	int					**map;
	t_pnt				map_size;
	t_vec				ppos;
	int					tsize;
	t_vec				dir_vec;
	t_vec				cam_vec;
}						t_env;

int						exit_prog(int error);
t_env					*setup_env(void);
t_env					*get_env(void);
void					putpixel(int x, int y, float hue);

#endif
