/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:26:50 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/16 17:56:46 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# define MAX_INT 2147483647
# define intf uint_fast8_t
# define intl uint_least8_t
# define W_WDTH 800
# define W_HGHT 800

# include "../libft/libft.h"
# include <SDL.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>

typedef struct			s_pnt
{
	unsigned int		x;
	unsigned int		y;
}						t_pnt;

typedef struct			s_img
{
	int					*data;
	int					bpp;
	int					l_size;
}						t_img;

typedef struct			s_env
{
	SDL_Window			*win_p;
	SDL_Event			event;
	t_img				img;
}						t_env;

int						exit_prog(int error);
t_env					*setup_env(void);
t_env					*get_env(void);

#endif
