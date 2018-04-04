//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

#include "stdio.h"

void    check_basic(t_gen *st)
{
	int start;
	int end;

	start = 0;
	end = 0;
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->start == 1)
			start++;
		else if (st->rooms->end == 1)
			end++;
		st->rooms = st->rooms->next;
	}
	if (start != 1 || end != 1)
		ft_error();
}

void    get_data(char *line, t_gen *st)
{
	if (ft_strchr(line, '-'))
	{
		check_basic(st);
		if (st->matrix == NULL)
			create_matrix(st);
		get_link_data(line, st);
	}
	else
		get_room_data(line, st);
}
