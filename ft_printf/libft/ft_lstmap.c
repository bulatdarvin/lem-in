/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:57:59 by ssilvana          #+#    #+#             */
/*   Updated: 2019/09/06 19:58:02 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_del(void *content, size_t contsize)
{
	(void)contsize;
	free(content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *t;
	t_list *elem;
	t_list *first;

	if (lst == 0 || f == 0)
		return (NULL);
	t = f(lst);
	first = ft_lstnew(t->content, t->content_size);
	if (first == 0)
		return (NULL);
	elem = first;
	while (lst->next)
	{
		lst = lst->next;
		t = f(lst);
		elem->next = ft_lstnew(t->content, t->content_size);
		if (elem->next == 0)
		{
			ft_lstdel(&first, &ft_del);
			return (NULL);
		}
		elem = elem->next;
	}
	return (first);
}
