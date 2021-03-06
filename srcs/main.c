/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/29 21:50:23 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void		liberate(t_env *env)
{
	int i;

	i = -1;
	while (++i < TEXNBR)
		SDL_FreeSurface(env->surtex[i]);
	if (env->minimap.init)
		SDL_FreeSurface(env->minimap.surf);
	SDL_DestroyWindow(env->win_p);
}

int			exit_prog(int error)
{
	if (!error)
		ft_putendl("Usage : wolf3d [map]");
	else if (error == 1)
		perror("wolf3d");
	else if (error == 2)
		ft_putendl("wolf3d : invalid map.");
	else if (error == 3)
		ft_putendl("wolf3d : parsing error.");
	else if (error == 4)
		ft_putendl("wolf3d : invalid map (liar).");
	else if (error == 5)
		ft_putendl("wolf3d : missing textures or/and font.");
	else if ((error = 42) && (SDL_WasInit(SDL_INIT_VIDEO)))
	{
		liberate(get_env());
		TTF_Quit();
		SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		SDL_Quit();
		return (0);
	}
	exit(64);
}

static void	event_loop(t_env *env)
{
	int			running;
	SDL_Event	event;

	running = 1;
	SDL_SetSurfaceRLE(env->surf, 1);
	draw_window(env);
	SDL_UpdateWindowSurface(env->win_p);
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (env->state[SDL_SCANCODE_ESCAPE]))
				running = 0;
			if (event.type == SDL_KEYDOWN)
				flags(env, event);
		}
		movements(env);
	}
}

int			main(const int argc, const char **argv)
{
	t_env		*env;
	t_map		*map;

	if (argc != 2 || !argv[1])
		return (exit_prog(0));
	if (!(map = parser(open(argv[1], O_RDONLY))))
		return (exit_prog(2));
	env = setup_env(*map);
	if (menu(env))
		event_loop(env);
	exit_prog(42);
	return (0);
}
