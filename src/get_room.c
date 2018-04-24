//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

int    check_room(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] != ' ')
		ft_error();
	else
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] != ' ')
		ft_error();
	else
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}


int     check_same_coor(t_gen *st, int x, int y)
{
	st->rooms = st->rc;
	while (st->rooms->next)
	{
		if (st->rooms->x == x && st->rooms->y == y)
			return (0);
		st->rooms = st->rooms->next;
	}
	if (st->rooms->x == x && st->rooms->y == y)
		return (0);
	return (1);
}

int     check_start(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms->next)
	{
		if (st->rooms->start)
			return (0);
		st->rooms = st->rooms->next;
	}
	if (st->rooms->start)
		return (0);
	return (1);
}

int     check_end(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms->next)
	{
		if (st->rooms->end)
			return (0);
		st->rooms = st->rooms->next;
	}
	if (st->rooms->end)
		return (0);
	return (1);
}

char    *get_room_data(char *line, t_gen *st)
{
	char **array;

	if (line[0] == '#' && ft_strcmp(line, "##start") != 0 && ft_strcmp(line, "##end") != 0)
	{
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		line = get_data(line, st);
		return (line);
	}
	if (st->rooms->name != NULL)
	{
		st->rooms->next = new_room();
		st->rooms->next->index = st->rooms->index + 1;
		st->rooms = st->rooms->next;
	}
	if (ft_strcmp(line, "##start") == 0)
	{
		if (!check_start(st))
			ft_error();
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		st->rooms->start = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (!check_end(st))
			ft_error();
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		st->rooms->end = 1;
	}
	if (check_room(line) == 0)
		ft_error();
	array = ft_strsplit(line, ' ');
	if (array_len(array) != 3)
		ft_error();
	if (!check_same_coor(st, ft_atoi(array[1]), ft_atoi(array[2])))
		ft_error();
	st->rooms->name = ft_strdup(array[0]);
	st->rooms->x = ft_atoi(array[1]);
	st->rooms->y = ft_atoi(array[2]);
	free_array(array);
	return (line);
}
