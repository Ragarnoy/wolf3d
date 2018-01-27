/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:22:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/28 00:30:40 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

static void	hslpixel(int x, int y, t_hsl cl)
{
	get_env()->data[y * W_WDTH + x] = ft_hsl_to_rgb(cl) & 0x00FFFFFF;
}

static void	line(int y, t_hsl cl)
{
	int	i;

	i = -1;
	while (++i < W_WDTH)
		hslpixel(i, y, cl);
}

static void	fade(int y)
{
	int		i;
	float	dif;
	int		val;
	t_hsl	shift;

	val = 20;
	i = -1;
	dif = 0.20;
	shift.h = 136;
	shift.s = 0.6;
	shift.l = dif;
	while (++i < val)
	{
		line(y, shift);
		shift.l += dif / val;
		y++;
	}
	while (--i > 0)
	{
		line(y, shift);
		shift.l -= dif / val;
		y++;
	}
}

static int	event_loop(t_env *env, t_fnt font)
{
	int			y;
	SDL_Event	event;

	y = -1;
	while (1)
	{
		if (y >= W_HGHT - 10)
			y = -5;
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (env->state[SDL_SCANCODE_ESCAPE]))
				return (0);
			else if (event.type == SDL_KEYDOWN)
				return (1);
		}
		fade(y);
		y += 10;
		SDL_BlitSurface(font.surfnt[0], NULL, env->surf, NULL);
		if (y < W_HGHT / 2)
			SDL_BlitSurface(font.surfnt[1], NULL, env->surf, &font.txtr);
		SDL_UpdateWindowSurface(env->win_p);
	}
	return (0);
}

int			menu(t_env *env)
{
	t_fnt		fonts;
	SDL_Color	clr;

	clr = (SDL_Color){0, 0, 0, 0};
	fonts.fnt[0] = TTF_OpenFont("./tex/justicegrad.ttf", 510);
	fonts.fnt[1] = TTF_OpenFont("./tex/D3Digitalism.ttf", 200);
	fonts.surfnt[0] = TTF_RenderText_Blended(fonts.fnt[0], "WOLF3D", clr);
	fonts.surfnt[1] = TTF_RenderText_Blended(fonts.fnt[1], "PRESS START", clr);
	fonts.txtr = (SDL_Rect){W_WDTH / 8, (W_HGHT / 8) * 7, 0, 0};
	TTF_CloseFont(fonts.fnt[0]);
	TTF_CloseFont(fonts.fnt[1]);
	if (!event_loop(env, fonts))
	{
		SDL_FreeSurface(fonts.surfnt[0]);
		SDL_FreeSurface(fonts.surfnt[1]);
		return (0);
	}
	else
	{
		SDL_FreeSurface(fonts.surfnt[0]);
		SDL_FreeSurface(fonts.surfnt[1]);
		return (1);
	}
}
