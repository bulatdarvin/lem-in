/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:16:30 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/06 14:51:18 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_abs(int a)
{
	return (a > 0 ? a : -a);
}

static void		zap(char *a, intmax_t n, int size)
{
	int		tmp;

	if (n == 0)
		a[0] = '0';
	while (size > 0 && n != 0)
	{
		tmp = ft_abs(n % 10);
		if (tmp == -8)
			tmp = 8;
		a[size - 1] = tmp + '0';
		n = n / 10;
		size--;
	}
}

static	char	*sozd(int min, int size, intmax_t n)
{
	char *a;

	if (min == -1)
	{
		a = ft_strnew(size + 1);
		if (a == 0)
			return (NULL);
		a[0] = '-';
		zap(a, n, size);
	}
	else
	{
		a = ft_strnew(size);
		if (a == 0)
			return (NULL);
		zap(a, n, size);
	}
	return (a);
}

int				num_size(intmax_t num)
{
	int size;

	size = 1;
	while (num / 10 != 0)
	{
		size++;
		num = num / 10;
	}
	return (size);
}

char			*ft_itoa(intmax_t n)
{
	int			size;
	int			min;
	char		*a;

	min = 1;
	if (n < 0)
		min = -1;
	size = num_size(n);
	a = sozd(min, size, n);
	if (a == 0)
		return (NULL);
	return (a);
}
