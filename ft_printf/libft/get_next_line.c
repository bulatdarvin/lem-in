/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:55:43 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/23 21:55:44 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*get_lst(const int fd, t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	if (tmp == 0)
		return (0);
	ft_lstadd(lst, tmp);
	return (tmp);
}

int		readstr(const int fd, char **line)
{
	int		ret;
	char	a[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, a, BUFF_SIZE)))
	{
		a[ret] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, a);
		if (*line == NULL)
			return (-1);
		free(tmp);
		if ((ft_strchr(a, '\n')))
			break ;
	}
	return (ret);
}

int		copy(char **line, char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_strnew(i);
	if (!*line)
		return (0);
	ft_strncpy(*line, str, i);
	return (i);
}

void	deletion(char *tmp)
{
	tmp[0] = '\0';
	free(tmp);
}

int		get_next_line(const int fd, char **line)
{
	int				buffer;
	char			*tmp;
	char			buf[BUFF_SIZE];
	static	t_list	*head;
	t_list			*elem;

	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL ||
		(read(fd, buf, 0)) < 0 || !(elem = get_lst(fd, &head)))
		return (-1);
	if (!(readstr(fd, (char**)&(elem->content))) &&
		(!((char*)elem->content)[0] || (char*)elem->content == NULL))
		return (0);
	buffer = copy(line, (char*)elem->content);
	tmp = elem->content;
	if (tmp[buffer])
	{
		elem->content = ft_strdup(&tmp[buffer + 1]);
		deletion(tmp);
	}
	else
		deletion(tmp);
	return (1);
}
