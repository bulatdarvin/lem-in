/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:45:55 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/06 19:45:58 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *a;

	if (alst)
	{
		while (*alst)
		{
			a = (*alst);
			(*alst) = (*alst)->next;
			del((a)->content, (a)->content_size);
			ft_memdel((void**)&a);
		}
		free(*alst);
	}
}
