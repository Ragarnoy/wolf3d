/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:26:50 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/28 19:16:20 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define MAX_INT 2147483647
# define INTF uint_fast8_t
# define INTL uint_least8_t
# define W_WDTH 2560
# define W_HGHT 1440
# define SPWN 120
# define WALL 35
# define THREAD_NBR 32
# define TEXNBR 4
# define FNTNBR 2

# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <SDL.h>
# include <SDL_thread.h>
# include "SDL_ttf.h"

typedef struct			s_fnt
{
	TTF_Font			*fnt[FNTNBR];
	SDL_Surface			*surfnt[FNTNBR];
	SDL_Rect			txtr;
}						t_fnt;

typedef struct			s_wall
{
	int					top;
	int					foot;
	int					perceived;
}						t_wall;

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
	double				ntile[2];
	double				ray[2];
	int					step[2];
	int					map_pos[2];
	double				dif[2];
	float				relative_pos;
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
	int					tsize;
	const Uint8			*state;
	SDL_Window			*win_p;
	SDL_Event			event;
	SDL_Surface			*surf;
	SDL_Surface			*surtex[TEXNBR];
	double				ppos[2];
	double				dir_vec[2];
	double				cam_vec[2];
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
void					flags(t_env *env, SDL_Event event);
void					minimap(t_env *env);
void					draw_window(t_env *env);
int						menu(t_env *env);

#endif
