/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/22 18:36:36 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int	exit_prog(int error)
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
}

int	main(void)
{
	t_env		*env;
	int			running;
	SDL_Event	event;

	running = 1;
	env = setup_env();
	raycasting(env);
	SDL_UpdateWindowSurface(env->win_p);
	while (running)
		while (SDL_PollEvent(&event))
		{
			movements(env);
			if ((event.type == SDL_QUIT) || (env->state[SDL_SCANCODE_ESCAPE]))
				running = 0;
			SDL_PumpEvents();
		}
	SDL_DestroyWindow(env->win_p);
	SDL_Quit();
	return (0);
}

/*
 * ligne 29 pour maj la fenetre
 * Sinon pour l'instant la fenetre va etre vide, normal
 * voila
*/
