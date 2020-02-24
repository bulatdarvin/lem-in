/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:37:53 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/06 16:14:37 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		putn(long t, int fd)
{
	if (t >= 10)
		putn(t / 10, fd);
	ft_putchar_fd(t % 10 + '0', fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	long t;

	t = n;
	if (t < 0)
	{
		ft_putchar_fd('-', fd);
		t = t * (-1);
	}
	putn(t, fd);
}
