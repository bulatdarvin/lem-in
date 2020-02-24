#include "ft_printf/includes/struct.h"

#define START -1
#define END -2

typedef	struct s_room
{
	char	*name;
	int		isvisited;
	int		x;
	int		y;
	struct s_room	**links;
	struct s_room	*next;
	int		links_size;
	int		state;
	int		used;
	struct s_room	*bfs_prev;
}		t_room;

typedef struct s_farm
{
	size_t	rooms_count;
	t_room	*rooms;
	t_room	*start;
	t_room	*end;
	size_t	ants_count;
//	int		**links;
}		t_farm;

typedef	struct s_path
{
	t_room		*room;
	struct s_path	*next;	
}				t_path;

typedef	struct s_path_list
{
	t_path	*path;
	int		size;
	struct s_path_list *next;
}			t_plist;

typedef	struct s_ant
{
	t_path	*pos;
	int		used;
	int		id;
	struct s_ant *next;
}			t_ant;

void	delete_ants(t_ant *ant)
{
	t_ant *tmp;

	if (ant)
	{
		while (ant)
		{
			tmp = ant->next;
			free(ant);
			ant = tmp;
		}
	}
}

void	delete_rooms(t_room *room)
{
	t_room	*tmp;

	if (room)
	{
		while (room->next)
		{
			tmp = room->next;

			free(room->name);
			free(room->links);
			free(room);
			room = tmp;
		}
		free(room);
		free(room->name);
		free(room->links);
	}
}

void	delete_farm(t_farm	*farm)
{
	if (farm)
	{
		delete_rooms(farm->rooms);
		free(farm);
	}
}

void	ft_error(t_farm *farm, char *str)
{
	delete_farm(farm);
	ft_putendl(str);
	exit(1);
}

int		is_comment(char	*str)
{
	if (str[0] == '#')
		return (1);
	return (0);
}

int		ft_isnum(char *str)
{
	int		i;
	int		digits;

	i = 0;
	digits = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		digits++;
	}
	return ((!str[i] && digits) ? 1 : 0);
}

t_room	*find_room(t_room *rooms, char *str)
{
	while (rooms)
	{
		if (ft_strequ(str, rooms->name))
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

t_room	*create_room(t_farm *farm, char **str)
{
	t_room *room;

	if (!ft_isnum(str[1]) || !ft_isnum(str[2]))
		ft_error(farm, "Not numbers for position");
	if (find_room(farm->rooms, str[0]))
	{
		//ft_printf("%s  %s\n", farm->rooms->name, str[0]);
		ft_error(farm, "Double room with same name");
	}
	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	room->links = NULL;
	room->name = ft_strnew(ft_strlen(str[0]));
	ft_strcpy(room->name, str[0]);
	room->x = ft_atoi(str[1]);
	room->y = ft_atoi(str[2]);
	room->state = 0;
	room->used = 0;
	room->bfs_prev = NULL;
	room->links_size = 0;
	room->next = NULL;
	room->isvisited = 0;
	return (room);
}


int		add_room(t_farm *farm, char *tmp)
{
	char	**str;
	int		i;
	t_room *room;

	i = 0;
	str = ft_strsplit(tmp, ' ');
	while (str[i])
		i++;
	if (i == 3)
	{
		farm->rooms_count++;
		room = create_room(farm, str);
		room->next = farm->rooms;
		farm->rooms = room;
	}
	ft_memdeltab(str);
	return (i == 3 ? 0 : 1);	
}

void	start_or_end(t_farm	*farm, char *str, int fd)
{
	if (ft_strequ(str, "##start"))
	{
		if (farm->start != NULL)
			ft_error(farm, "Has 2 starts");
		free(str);
		get_next_line(fd, &str);
		if (is_comment(str))
			ft_error(farm, "Invalid input");
		add_room(farm, str);
		farm->start = farm->rooms;
		farm->rooms->state = START;	
	}
	if (ft_strequ(str, "##end"))
	{
		if (farm->end != NULL)
			ft_error(farm, "Has 2 ends");
		free(str);
		get_next_line(fd, &str);
		if (is_comment(str))
			ft_error(farm, "Invalid input");
		add_room(farm, str);
		farm->end = farm->rooms;
		farm->rooms->state = END;	
	}
	free(str);
}

int		linked(t_room *r1, t_room *r2)
{
	int i;
	t_room *tmp;

	i = 0;
/*	tmp = r1;
	while (r1->links[i])
	{
		if (r1->links[i] == r2)
			return (1);
		i++;
	}
	i = 0;
	while (r2->links[i])
	{
		if (r2->links[i] == tmp)
			return (1);
		i++;
	}
*/	return (0);
}

void	link_rooms(t_farm *farm, char *tmp)
{
	t_room *r1;
	t_room *r2;
	char	**str;
	int		i;

	i = 0;
	str = ft_strsplit(tmp, '-');
	while (str[i])
		i++;
	if (i != 2)
		return ;
	r1 = find_room(farm->rooms, str[0]);
	r2 = find_room(farm->rooms, str[1]);
	ft_memdeltab(str);
	if (!r1 || !r2)
		ft_error(farm, "No room to link");
	if (r1->links == NULL)
		r1->links = (t_room **)malloc(sizeof(t_room *) * farm->rooms_count);
	if (r2->links == NULL)
		r2->links = (t_room **)malloc(sizeof(t_room *) * farm->rooms_count);
	if (linked(r1, r2))
	{
		ft_printf("r1: %s  r2: %s\n", r1->name, r2->name);
		ft_error(farm, "Has double linked");
	}
	if (r1 == farm->start)
	{
		r1->links[r1->links_size++] = r2;
		r1->links[r1->links_size] = NULL;
	}
	else if (r2 == farm->start)
	{
		r2->links[r2->links_size++] = r1;
		r2->links[r2->links_size] = NULL;
	}
	else
	{
		r1->links[r1->links_size++] = r2;
		r1->links[r1->links_size] = NULL;
		r2->links[r2->links_size++] = r1;
		r2->links[r2->links_size] = NULL;
	}
}

void		reverse_room(t_room **room)
{
	t_room	*next;
	t_room *cur;
	t_room *prev;

	if (room && *room)
	{
		prev = NULL;
		cur = *room;
		next = NULL;
		while (cur)
		{
			next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		*room = prev;
	}
}

t_farm		*create_farm(int fd)
{
	t_farm	*farm;
	char	*str;
	int		check;
	
	farm = (t_farm*)malloc(sizeof(t_farm));
	check = 0;
	farm->rooms = NULL;
	farm->rooms_count = 0;
	farm->start = NULL;
	farm->end = NULL;
	if (get_next_line(fd, &str) > 0)
	{
		farm->ants_count = ft_atoi(str);
		free(str);
	}
	else
		ft_error(farm, "Open non-existing file or directory");
	while(get_next_line(fd, &str) > 0)
	{
		if (is_comment(str))
		{
			start_or_end(farm, str, fd);
			continue ;
		}
		if (check == 0)
			check = add_room(farm, str);
		if (check == 1)
			link_rooms(farm, str);
		free(str);
	}
	reverse_room(&(farm->rooms));
	return (farm);
}

t_path	*make_path(t_room *room)
{
	t_path *path;

	path = (t_path *)malloc(sizeof(t_path));
	path->next = NULL;
	path->room = room;
	return (path);
}

t_path	*add_to_path(t_path	**path, t_room *room)
{
	t_path	*tmp;

	if (!*path)
		*path = make_path(room);
	else
	{
		tmp = *path;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_path *)malloc(sizeof(t_path));
		tmp->next->room = room;
		tmp->next->next = NULL;
	}
	return (tmp);
}

t_path	*copy_path(t_path	*path)
{
	t_path	*tmp;

	while (path)
	{
		tmp = add_to_path(&tmp, path->room);
		path = path->next;
	}
	return (tmp);
}


t_room	*pop_room(t_path	**path)
{
	t_path	*start;
	t_room	*room;

	if (!path && !*path)
		return (NULL);
	room = (*path)->room;
	start = *path;
	(*path) = (*path)->next;
	free(start);
	start = NULL;
	return (room);	
}

void	go_through_links(t_path	**queue, t_room	**links, t_room	*prev)
{
	int i;

	i = 0;
	while (links[i])
	{
		if (links[i]->isvisited == 0 && links[i]->used == 0)
		{
			add_to_path(queue, links[i]);
			links[i]->isvisited = 1;		
			links[i]->bfs_prev =  prev;
		}
		i++;
	}
	t_path	*path;
	path = *queue;
}

void	delete_path(t_path	*path)
{
	t_path	*tmp;

	if (path)
	{
		while(path)
		{
			tmp = path->next;
			free(path);
			path = tmp;
		}
	}
}

void	delete_plist(t_plist *list)
{
	t_plist *tmp;

	if (list)
	{
		while (list)
		{
			tmp = list->next;
			delete_path(list->path);
			free(list);
			list = tmp;
		}
	}
}

void	reset(t_farm *farm, t_room *room, int tmp)
{
	while (room)
	{
		room->bfs_prev = NULL;
		room->isvisited = 0;
		room = room->next;
	}
	farm->start->used= 0;
	farm->end->used = 0;
	if (linked(farm->start, farm->end) && tmp)
		farm->end->used = 1;
}

void		reverse_path(t_path **path)
{
	t_path	*next;
	t_path *cur;
	t_path *prev;

	if (path && *path)
	{
		prev = NULL;
		cur = *path;
		next = NULL;
		while (cur)
		{
			next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		*path = prev;
	}
}

t_path	*path_for_bfs(t_room *room, t_farm *farm)
{
	t_path	*path;

	path = NULL;
	while (room)
	{
		if (room != farm->start)
			add_to_path(&path, room);
		room->used = 1;
		room = room->bfs_prev;
	}
	reverse_path(&path);
	return (path);
}

t_path	*ft_bfs(t_farm	*farm, int tmp)
{
	t_path	*queue;
	t_room	*room;

	reset(farm, farm->rooms, tmp);
	queue = make_path(farm->start);
	farm->start->isvisited = 0;
	while (queue)
	{
		room = pop_room(&queue);
		if (room == farm->end)
		{
			delete_path(queue);
			return(path_for_bfs(farm->end, farm));
		}
		else
			go_through_links(&queue, room->links, room);
	}
	return (NULL);
}

int		path_size(t_path *path)
{
	int size;

	size = 0;
	while (path)
	{
		size++;
		path = path->next;
	}
	return (size - 2);
}

void	add_list_of_path(t_plist	**list, t_path *path)
{
	t_plist *tmp;

	if (!*list)
	{
		*list = (t_plist *)malloc(sizeof(t_plist));
		(*list)->next = NULL;
		(*list)->path = path;
		(*list)->size = path_size(path);
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_plist *)malloc(sizeof(t_plist));
		tmp->next->path = path;
		tmp->next->size = path_size(path);
		tmp->next->next = NULL;
	}
}
int		list_size(t_plist *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	swap_pathes(t_path **p1, t_path **p2, t_plist **list)
{
	t_path *tmp;
	int i;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	i = (*list)->size;
	(*list)->size = (*list)->next->size;
	(*list)->next->size = i;
}

void	sort_list_by_length(t_plist **list)
{
	t_plist *tmp;
	t_plist *head;

	head = *list;
	while (head->next)
	{
		tmp = head;
		while (tmp->next)
		{
			if (tmp->size > tmp->next->size)
				swap_pathes(&(tmp->path), &(tmp->next->path), &tmp);
			tmp = tmp->next;
		}
		head = head->next;
	}
}

t_ant	*init_ant(t_farm *farm)
{
	t_ant *ants;
	t_ant *head;
	int		i;

	i = 2;
	head = (t_ant *)malloc(sizeof(t_ant));
	ants = head;
	ants->pos = NULL;
	ants->id = 1;
	ants->used = 1;
	ants->next = NULL;
	while (i <= farm->ants_count)
	{
		ants->next = (t_ant *)malloc(sizeof(t_ant));
		ants = ants->next;
		ants->pos = NULL;
		ants->used = 1;
		ants->next = NULL;
		ants->id = i;
		i++;
	}
	return (head);
}

int		help_to_solve(t_plist *list, int ants, int i)
{
	t_plist *head;
	int num;
	int tmp;

	tmp = 0;
	num = 0;
	head = list;
	while (tmp++ < i)
		list = list->next;
	if (tmp == 0)
		return (0);//ASafaf
	while (head != list)
	{
		num += list->size - head->size;
		head = head->next;
	}
	return (num);
}

t_ant 	*ant_pathes(int ants, t_plist *pathes, t_farm *farm)
{
	t_ant 	*tmp_ant;
	t_ant	*ant;
	t_plist *tmp;
	int		num;
	int		i;

	ant = init_ant(farm);
	tmp_ant = ant;	
	while (ants)
	{
		i = 0;
		while (i < list_size(pathes) && ants && ants > help_to_solve(pathes, ants, i))
		{
			tmp = pathes;
			num = 0;
			while (num++ < i)
				tmp = tmp->next;
			ant->pos = tmp->path;
			ant = ant->next;
			ants--;
			i++;
		}
	}
	return (tmp_ant);
}

int		move_forward(t_ant **ant, int ind, int count)
{
	t_ant *tmp;

	tmp = *ant;
/*	if (tmp->pos == NULL)
	{
		count--;
		*ant = (*ant)->next;
	}
*/	while (ind-- && tmp && tmp->pos)
	{
	//	tmp->pos = tmp->pos->next;
		tmp = tmp->next;
	}
	return (count);
}

int		print_room(t_ant *ant, int ind, int count, int rooms)
{
	static int i = 1;
	if (ant->pos)
	{
		while (ind-- && ant && rooms)
		{/*
			while (!ant->pos && ant->next)
			{
				ant->used = 0;
				ant = ant->next;
				//count--;
			}
			if (!ant->pos && !ant->next)
			{
				ft_printf("break\n");
				break ;
			}
			*/
			while (!ant->used && ant)
				ant = ant->next;
			rooms--;
			//if (!ant->pos)
			//	ft_printf("WWWWW");
			if (ant->used)
				ft_printf("L%d-%s", ant->id, ant->pos->room->name);
			ant->pos = ant->pos->next;
			ant = ant->next;
			while (!ant->pos && ant->next)
			{
				ant->used = 0;
				ant = ant->next;
				if (!ant)
					break ;
			//	count--;				
			}
			//ant = ant->next;
			if (!ant->pos && !ant->next)
			{
				ft_printf("break\n");
				break ;
			}
			if (ant)
				ft_printf(" ");
		}
		ft_printf("\n");
		ft_printf("I: %d   R:  %d   IND: %d\n", i++, rooms, ind);
	}
	return (count);
}

int		count_ind(t_ant *ant)
{
	int i;
	t_ant *tmp;

	i = 1;
	if (ant)
		if (ant->next)
		{
			tmp = ant->next;
			while (ant->pos->room != tmp->pos->room && tmp)
			{
				i++;
				tmp = tmp->next;
			}
		}
	return (i);
}

void	head_mv(t_ant **head, int ind)
{
	while (ind-- && *head)
		*head = (*head)->next;
}

void	movement(t_ant	*ant, int count, int rooms)
{
	int ind;
	t_ant *head;

	ind = count_ind(ant);
	head = ant;
	head_mv(&head, ind);
	while (ant && count != 0)
	{
		ft_printf("ASFS\n");
		count = print_room(ant, ind, count, rooms);
		//count = move_forward(&ant, ind, count);
		ind += count_ind(head);
		head_mv(&head, ind);
		while (!ant->pos)
		{
		//	ft_printf("%d    count:  %d\n", ant->id, count);
			count--;
			ant->used = 0;
			ant = ant->next;
			if (!ant)
				break ;
		}
	}
}

void	print_path(t_path *path)
{
	ft_printf("NEW PATH:\n");
	while (path)
	{
		ft_printf("%s\n", path->room->name);
		path = path->next;
	}
}
int 	main()
{
	t_farm *farm;
	t_path *path;
	t_plist *list;
	t_ant *ant;
	int		tmp;

	tmp = 0;
	int fd = open("maps/test", O_RDONLY);
	farm = create_farm(0);
	list = NULL;
	while (1)
	{
		path = ft_bfs(farm, tmp);
		//ft_printf("fasf\n");
		if (path == NULL)
			break ;
		tmp = 1;
		add_list_of_path(&list, path);
//		print_path(path);
//		delete_path(path);
	}
	ft_printf("%d\n", list_size(list));
	if (!list_size(list))
		ft_error(farm, "No solution");
	sort_list_by_length(&list);
	ant = ant_pathes(farm->ants_count, list, farm);
/*	t_ant *t;
	t = ant;
	t = t->next->next;
	while (t->pos)
	{
		ft_printf("%s\n", t->pos->room->name);
		t->pos = t->pos->next;
	}
*/	movement(ant, farm->ants_count, farm->rooms_count - 1);
	delete_farm(farm);
	delete_plist(list);
	delete_ants(ant);
	return (0);
}