/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:19:35 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 21:59:44 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*d;
	size_t	i;

	i = 0;
	d = (char*)s;
	while (i < n)
	{
		if (d[i] == (char)c)
			return (d + i);
		i++;
	}
	return (NULL);
}
