/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:48:21 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/05 19:20:52 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy(char const *s, char *a, size_t len)
{
	size_t i;

	i = 0;
	while (*s == '\t' || *s == '\n' || *s == ' ')
		s++;
	while (i < len)
	{
		a[i] = *s;
		s++;
		i++;
	}
}

char		*ft_strtrim(char const *s)
{
	size_t		l;
	size_t		k;
	char		*a;
	const char	*tmp;

	l = 0;
	if (s == 0)
		return (NULL);
	tmp = s;
	k = ft_strlen(s);
	while ((s[l] == '\t' || s[l] == '\n' || s[l] == ' ') && s[l] != '\0')
		l++;
	while (s[k - 1] == '\t' || s[k - 1] == '\n' || s[k - 1] == ' ')
		k--;
	if (k < l)
		k = l;
	a = ft_strnew(k - l);
	if (a == 0)
		return (NULL);
	ft_copy(tmp, a, k - l);
	return (a);
}
