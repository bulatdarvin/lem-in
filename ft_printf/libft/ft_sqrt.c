/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:43:58 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/26 13:02:29 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_abs(float a)
{
	return (a > 0 ? a : -a);
}

int				ft_sqrt(int a)
{
	float min;
	float max;
	float mid;

	min = 0;
	max = a;
	while (ft_abs(max - min) > 0.01)
	{
		mid = (max + min) / 2.0;
		if (mid * mid < (float)a)
			min = mid;
		else
			max = mid;
	}
	if ((int)(max - 0.5) == (int)max)
		return ((int)max + 1);
	else
		return ((int)max);
}
