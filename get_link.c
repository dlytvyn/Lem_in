//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

void    check_name(char *name, t_gen *st)
{
	int i;

	i = 0;
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (ft_strcmp(name, st->rooms->name) == 0)
			i++;
		st->rooms = st->rooms->next;
	}
	if (i != 1)
		ft_error();
}


int     search_in(char *name, t_gen *st)
{
	st->rooms= st->rc;
	while (st->rooms)
	{
		if (ft_strcmp(st->rooms->name, name) == 0)
			return (st->rooms->index);
		st->rooms = st->rooms->next;
	}
}

void    set_link(char **array, t_gen *st)
{
	int l1;
	int l2;

	l1 = search_in(array[0], st);
	l2 = search_in(array[1], st);
	if (l1 == l2)
		ft_error();
	st->matrix[l1][l2] = 1;
	st->matrix[l2][l1] = 1;
}

void    get_link_data(char *line, t_gen *st)
{
	char **array;

	array = ft_strsplit(line, '-');
	if (array_len(array) != 2)
		ft_error();
	check_name(array[0], st);
	check_name(array[1], st);
	set_link(array, st);
}
