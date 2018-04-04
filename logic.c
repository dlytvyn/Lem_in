//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

#include <stdio.h>

int     search_first(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->start)
			return (st->rooms->index);
		st->rooms = st->rooms->next;
	}
}

int     search_last(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->end)
			return (st->rooms->index);
		st->rooms = st->rooms->next;
	}
}

int     path_num(t_gen *st)
{
	int j;
	int res;

	st->first = search_first(st);
	st->last = search_last(st);
	j = 0;
	res = 0;
	while (j < st->size)
	{
		if (st->matrix[st->first][j] == 1)
			res++;
		j++;
	}
	return (res);
}

void    search_path(t_gen *st)
{
	int i;
	int j;

	i = 0;
	j = 0;
	st->ways->path->in = st->first;
	while (j < st->size)
	{
		if (st->matrix[st->first][j] == 1)
		{
			st->ways->path->next = new_path();
			st->ways->path = st->ways->path->next;
			st->ways->path->in = j;

			st->matrix[st->first][j] = 0;
			st->matrix[j][st->first] = 0;        // may be not right
		}
		j++;
	}
	while (i < st->size)
	{
		j = 0;
		while (j < st->size)
		{
			if (st->matrix[i][j] == 1)
			{
				st->ways->path->next = new_path();
				st->ways->path = st->ways->path->next;
				st->ways->path->in = j;

				st->matrix[i][j] = 0;
				st->matrix[j][i] = 0;        // may be not right
			}
			j++;
		}
		i++;
		(i == st->first) ? i++ : i;
	}
}

void    order(t_gen *st)
{
	int path;
	int i;

	i = 1;
	path = path_num(st);
	st->ways = new_ways();
	st->ways_copy = st->ways;
	while (i < path)
	{
		st->ways->next = new_ways();
		st->ways = st->ways->next;
		i++;
	}
	search_path(st);
}