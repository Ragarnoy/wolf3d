/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 12:09:00 by tlernoul          #+#    #+#             */
/*   Updated: 2016/12/23 17:28:51 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int i;
	int r;
	int neg;

	i = 0;
	r = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] > 6 && str[i] < 14))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + neg * (str[i] - '0');
		i++;
	}
	return (r);
}