/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:56:46 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 22:01:08 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	int		temp;
	char	*p;

	i = 0;
	temp = -1;
	p = (char*)s;
	while (p[i] != '\0')
	{
		if (p[i] == (char)c)
			temp = i;
		i++;
	}
	if (c == '\0')
		temp = i;
	if (temp >= 0)
		return (p + temp);
	return (NULL);
}
