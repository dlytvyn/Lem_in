//
// Created by Dmytro LYTVYN on 4/12/18.
//

#include "lem_in.h"

#include "stdio.h"

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

void    movement(t_gen *st)
{
	int l;
	int i;
	int j;
	int temp;

	l = 1;
	temp = 0;
	i = st->first;
	while (l <= st->ants)
	{
		j  = 0;
		while (l <= st->ants && j < st->size)
		{
			if (st->matrix[i][j])
			{
				temp = get_coor(st, i);
				set_room_busy(st, temp, 1);
				printf("L%d - %s", l, get_name(st, temp));                                                 // change this
				l++;
			}
		}
		l++;

	}
}