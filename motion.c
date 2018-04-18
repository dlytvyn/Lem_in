//
// Created by Dmytro LYTVYN on 4/12/18.
//

#include "lem_in.h"

#include "stdio.h"

char    *get_name(t_gen *st, int room)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->index == room)
			return (st->rooms->name);
		st->rooms = st->rooms->next;
	}
}

void    set_room_busy(t_gen *st, int room, int busy)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->index == room)
			st->rooms->busy = (busy == 1) ?  1 : 0;
		st->rooms = st->rooms->next;
	}
}

int     is_room_empty(t_gen *st, int room)
{
	int res;

	res = 0;
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->index == room && st->rooms->busy == 0)
			res = 1;
		st->rooms = st->rooms->next;
	}
	return (res);
}

int     get_coor(t_gen *st, int i)
{
	int j;
	double temp;
	int res;

	j = 0;
	temp = 0;
	res = 0;
	while (j < st->size)
	{
		if (st->matrix[i][j] > temp && is_room_empty(st, j))
		{
			temp = st->matrix[i][j];
			res = j;
		}
		j++;
	}
	return (res);
}

void    search_ways(t_gen *st)
{
	int     num;
	int     i;
	int     temp;

	st->ways = new_ways();
	num = path_num(st);
	while (num > 0)
	{
		if (st->ways->path->name)
		{
			st->ways->next = new_ways();
			st->ways = st->ways->next;
		}
		i = st->first;
		while (i != st->last)
		{
			temp = get_coor(st, i);
			set_room_busy(st, temp, 1);
			if (st->ways->path->name)
			{
				st->ways->path->next = new_path();
				st->ways->path = st->ways->path->next;
				st->ways->path->in = temp;
				st->ways->path->name = get_name(st, temp);
			}
			else
			{
				st->ways->path->in = temp;
				st->ways->path->name = get_name(st, temp);
			}
			i = temp;
		}
		num--;
	}
}