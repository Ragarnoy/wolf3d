/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:26:50 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 14:50:46 by tlernoul         ###   ########.fr       */
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

# include "../libft/libft.h"
# include "sdl/SDL.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>

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
	unsigned int		x;
	unsigned int		y;
}						t_pnt;

typedef struct			s_minimap
{
	int					init;
	SDL_Surface			*surf;
	SDL_Rect			dst;
}						t_minimap;

typedef struct			s_env
{
	int					*data;
	const Uint8			*state;
	SDL_Window			*win_p;
	SDL_Event			event;
	SDL_Surface			*surf;
	t_map				map;
	t_minimap			minimap;
	t_flags				flg;
}						t_env;

int						exit_prog(int error);
t_map					*parser(int fd);
t_env					*setup_env(void);
t_env					*get_env(void);
void					putpixel(int x, int y, float hue);
void					movements(t_env *env);
void					flags(t_env *env);
void					minimap(t_env *env);

#endif
