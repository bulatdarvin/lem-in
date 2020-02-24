/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:14:12 by ssilvana          #+#    #+#             */
/*   Updated: 2019/07/09 16:00:15 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\200')
		return (-128);
	if (s1[i] == '\200' && s2[i] == '\0')
		return (128);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}