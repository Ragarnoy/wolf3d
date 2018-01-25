/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:26:50 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/24 20:16:55 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define MAX_INT 2147483647
# define INTF uint_fast8_t
# define INTL uint_least8_t
# define W_WDTH 800
# define W_HGHT 800
# define SPWN 120
# define WALL 35
# define THREAD_NBR 8

# include "../libft/libft.h"
# include <SDL.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <SDL_thread.h>

typedef struct			s_vec
{
	double				x;
	double				y;
}						t_vec;

typedef struct			s_map
{
	unsigned int		wdth;
	unsigned int		hght;
	char				**map;
}						t_map;

typedef struct			s_flags
{
	INTL				minimap;
}						t_flags;

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

typedef struct			s_minimap
{
	int					init;
	SDL_Surface			*surf;
	SDL_Rect			dst;
}						t_minimap;

typedef struct			s_win_part
{
	t_pnt				a;
	t_pnt				b;
}						t_win_part;

typedef struct			s_env
{
	int					*data;
	const Uint8			*state;
	SDL_Window			*win_p;
	SDL_Event			event;
	SDL_Surface			*surf;
	t_vec				ppos;
	int					tsize;
	t_vec				dir_vec;
	t_vec				cam_vec;
	t_map				map;
	t_minimap			minimap;
	t_flags				flg;
}						t_env;

int						exit_prog(int error);
t_map					*parser(int fd);
t_env					*setup_env(t_map lul);
t_env					*get_env(void);
void					putpixel(int x, int y, float hue);
void					movements(t_env *env);
int						raycasting(void *tmp);
void					flags(t_env *env);
void					minimap(t_env *env);
void					draw_window(t_env *env);

#endif
