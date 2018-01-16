/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 18:07:37 by tlernoul          #+#    #+#             */
/*   Updated: 2018/01/16 18:16:42 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf.h"

void	putpixel(t_pnt pt, float hue)
{
	t_hsl hsl;

	hsl.h = hue;
	hsl.s = 1.0;
	hsl.l = 0.5;
	get_env()->img.data[pt.y * W_WDTH + pt.x] = ft_hsl_to_rgb(hsl) & 0x00FFFFFF;
}
