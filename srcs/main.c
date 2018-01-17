/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 23:57:24 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/17 15:50:33 by tle-gac-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

int	exit_prog(int error)
{
	if (!error)
		ft_putendl("Usage : wolf3d [map]");
	exit(-1);
}

void	test_tamere(t_env *env)
{
	
}

int	main(void)
{
	t_env		*env;
	//int			running = 1;
	//SDL_Event	event;

	env = setup_env();
	test_tamere(env);
	/*SDL_UpdateWindowSurface(env->win_p);
	while (running)
		while(SDL_PollEvent(&event))
			if((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				running = 0;
	SDL_DestroyWindow(env->win_p);
	SDL_Quit();*/
	return (0);
}

/*
 * ligne 29 pour maj la fenetre
 * Sinon pour l'instant la fenetre va etre vide, normal
 * voila
*/
