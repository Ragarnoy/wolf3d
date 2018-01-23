/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/23 14:53:26 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int			exit_prog(int error)
{
	if (!error)
		ft_putendl("Usage : wolf3d [map]");
	else if (error == 1)
		perror("wolf3d");
	else if (error == 2)
		ft_putendl("wolf3d : invalid map.");
	else if (error == 3)
		ft_putendl("wolf3d : parsing error");
	else if (error == 4)
		ft_putendl("wolf3d : invalid map (liar)");
	exit(-1);
	/*
	 * subsystem quit
	*/
}

static void	event_loop(t_env *env)
{
	int			running;
	SDL_Event	event;

	running = 1;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
		if (env->flg.minimap)
			minimap(env);
		flags(env);
		movements(env);
			if ((event.type == SDL_QUIT) || (env->state[SDL_SCANCODE_ESCAPE]))
				running = 0;
			SDL_PumpEvents();
		}
	}
}

int			main(const int argc, const char **argv)
{
	t_env		*env;
	t_map		*map;

	if (argc != 2 || !argv[1])
		return (exit_prog(0));
	if (!(map = parser(open(argv[1], O_RDONLY))))
		return(exit_prog(2));
	env = setup_env();
	env->map = *map;
	//ft_memset(env->data, 0xFFFFFFFF, 800 * 800 * 4);
	//minimap(env);
	SDL_UpdateWindowSurface(env->win_p);
	event_loop(env);
	SDL_DestroyWindow(env->win_p);
	SDL_Quit();
	return (0);
}

/*
 * ligne 15 pour maj la fenetre
 * Sinon pour l'instant la fenetre va etre vide, normal
 * voila
			if (env->state[SDL_SCANCODE_O])
				env->flg.minimap = !env->flg.minimap;
			if (env->flg.minimap)
				minimap(env);
*/
