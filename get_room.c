//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

int    check_room(char *line)
{
	int i;

	i = 0;
	while (line[i] && (ft_isdigit(line[i]) || ft_isalpha(line[i])))
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

void    get_room_data(char *line, t_gen *st)
{
	char **array;

	if (st->rooms->name != NULL)
	{
		st->rooms->next = new_room();
		st->rooms->next->index = st->rooms->index + 1;
		st->rooms = st->rooms->next;
	}
	if (ft_strcmp(line, "##start") == 0)
	{
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		st->rooms->start = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		st->rooms->end = 1;
	}
	if (line[0] == '#')
	{
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
	}
	if (check_room(line) == 0)
		ft_error();
	array = ft_strsplit(line, ' ');
	if (array_len(array) != 3)
		ft_error();
	st->rooms->name = ft_strdup(array[0]);
	st->rooms->x = ft_atoi(array[1]);
	st->rooms->y = ft_atoi(array[2]);
	free_array(array);
}
