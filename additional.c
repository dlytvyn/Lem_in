//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

t_path  *new_path(void)
{
	t_path  *path;

	path = (t_path*)malloc(sizeof(t_path));
	path->in = 0;
	path->next = NULL;
	return (path);

}

t_ways  *new_ways(void)
{
	t_ways  *ways;

	ways = (t_ways*)malloc(sizeof(t_ways));
	ways->path = new_path();
	ways->path_copy = ways->path;
	ways->index = 0;
	ways->next = NULL;
	return (ways);
}

void    ft_error(void)
{
	write(1, "Map Error\n", 10);
	exit(0);
}

t_rooms *new_room()
{
	t_rooms *elem;

	elem = (t_rooms*)malloc(sizeof(t_rooms));
	elem->x = 0;
	elem->y = 0;
	elem->name = NULL;
	elem->start = 0;
	elem->end = 0;
	elem->index = 0;
	elem->busy = 0;
	elem->next = NULL;
	return (elem);
}

void    add_str(t_gen *st, char *line)
{
	char    *tmp;

	tmp = ft_strdup(st->map);
	ft_strdel(&st->map);
	st->map = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	tmp = ft_strdup(st->map);
	ft_strdel(&st->map);
	st->map = ft_strjoin(tmp, line);
	ft_strdel(&tmp);
}

int     array_len(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void    free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}
