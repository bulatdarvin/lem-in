/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:46:24 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/03 21:58:33 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int t;

	i = 0;
	t = 0;
	if (*needle == 0)
		return ((char*)haystack);
	while (haystack[t] != '\0')
	{
		if (haystack[t] == needle[0])
		{
			i = 0;
			while (haystack[t + i] == needle[i] && needle[i])
				i++;
			if (needle[i] == '\0')
				return ((char*)(haystack + t));
		}
		t++;
	}
	return (NULL);
}
