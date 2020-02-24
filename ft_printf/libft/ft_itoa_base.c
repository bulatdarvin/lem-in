/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 16:50:18 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/13 16:50:20 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <inttypes.h>

static void		zap(char *a, uintmax_t n, int size, uintmax_t base)
{
	if (n == 0)
		a[0] = '0';
	while (size > 0 && n > 0)
	{
		if (n % base >= 10)
			a[size - 1] = n % base + 55;
		else
			a[size - 1] = n % base + '0';
		n = n / base;
		size--;
	}
}

static	char	*sozd(int size, uintmax_t n, uintmax_t base)
{
	char *a;

	a = ft_strnew(size);
	if (a == 0)
		return (NULL);
	zap(a, n, size, base);
	return (a);
}

char			*ft_itoa_base(uintmax_t n, uintmax_t base)
{
	uintmax_t	num;
	int			size;
	char		*a;

	size = 1;
	num = n;
	while (n / base != 0)
	{
		size++;
		n = n / base;
	}
	a = sozd(size, num, base);
	if (a == 0)
		return (NULL);
	return (a);
}
