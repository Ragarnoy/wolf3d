/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:26:50 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/17 21:39:40 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define MAX_INT 2147483647
# define intf uint_fast8_t
# define intl uint_least8_t
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

typedef struct			s_pnt
{
	unsigned int		x;
	unsigned int		y;
}						t_pnt;

typedef struct			s_env
{
	int					*data;
	SDL_Window			*win_p;
	SDL_Event			event;
	SDL_Surface			*surf;
}						t_env;

int						exit_prog(int error);
t_map					parser(int fd);
t_env					*setup_env(void);
t_env					*get_env(void);
void					putpixel(t_pnt, float hue);

#endif
