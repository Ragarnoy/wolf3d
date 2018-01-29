/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:22:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/29 21:50:49 by tlernoul         ###   ########.fr       */
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
		shift.h += 2;
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
	Uint32		y;
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
		y += 6;
		SDL_BlitSurface(font.surfnt[0], NULL, env->surf, NULL);
		SDL_BlitSurface(font.surfnt[1], NULL, env->surf, &font.txtr);
		fade(y);
		SDL_UpdateWindowSurface(env->win_p);
	}
	return (0);
}

int			menu(t_env *env)
{
	t_fnt		fonts;
	SDL_Color	clr;
	int			ret;

	clr = (SDL_Color){0, 0, 0, 0};
	if (!(fonts.fnt[0] = TTF_OpenFont("./tex/justicegrad.ttf", 510)))
		exit_prog(5);
	if (!(fonts.fnt[1] = TTF_OpenFont("./tex/D3Digitalism.ttf", 200)))
		exit_prog(5);
	fonts.surfnt[0] = TTF_RenderText_Blended(fonts.fnt[0], "WOLF3D", clr);
	fonts.surfnt[1] = TTF_RenderText_Blended(fonts.fnt[1], "PRESS START", clr);
	fonts.txtr = (SDL_Rect){W_WDTH / 8, (W_HGHT / 8) * 6, 0, 0};
	ret = event_loop(env, fonts);
	TTF_CloseFont(fonts.fnt[0]);
	TTF_CloseFont(fonts.fnt[1]);
	SDL_FreeSurface(fonts.surfnt[0]);
	SDL_FreeSurface(fonts.surfnt[1]);
	if (!ret)
		return (0);
	else
		return (1);
}
