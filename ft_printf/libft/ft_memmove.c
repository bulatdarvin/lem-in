/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:30:33 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 18:16:40 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (dst == 0 && src == 0)
		return (NULL);
	if (d < s)
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	else
	{
		d = d + len - 1;
		s = s + len - 1;
		while (i++ < len)
			*d-- = *s--;
	}
	return (dst);
}
