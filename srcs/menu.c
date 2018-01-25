/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:53:46 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/25 18:31:20 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

/*static void	callback(void *usrdata, Uint8 *stream, int len)
{
	t_env *env;

	env = (t_env*)usrdata;
	if (env->snd.audio_len == 0)
		return;
	len = ((Uint32)len > env->snd.audio_len ? env->snd.audio_len : len );
	SDL_MixAudio(stream, env->snd.audio_pos, len, SDL_MIX_MAXVOLUME);
	
	env->snd.audio_pos += len;
	env->snd.audio_len -= len;
}
*/
void		setup_sound(t_env *env)
{
	Uint8				*wav_buf;
	Uint32				wav_lgth;
	SDL_AudioDeviceID	deviceId;

	SDL_LoadWAV("./sound/menu.wav", &env->snd.spec, &wav_buf, &wav_lgth);
	deviceId = SDL_OpenAudioDevice("35CTL", 0, &env->snd.spec, NULL, 0);
	ft_putendl("crash2");
	if(SDL_QueueAudio(deviceId, wav_buf, wav_lgth) < 0)
		printf("%s\n",SDL_GetError());
	SDL_PauseAudioDevice(deviceId, 0);
	ft_putendl("crash3");
	if (env->snd.audio_len == 0)
		SDL_CloseAudio();
}
