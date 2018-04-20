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
	return (NULL);
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
	res = -1;
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

void    clear_this_path(t_gen *st, t_ways *cp)
{
	t_path *tmp;

	st->ways = cp;
	st->ways->path = st->ways->path_copy;
	while (st->ways->path)
	{
		tmp = st->ways->path->next;
		free(st->ways->path->name);
		free(st->ways->path);
		st->ways->path = tmp;
	}
	st->ways->path = new_path();
	st->ways->path_copy = st->ways->path;
}

void    check_empty_path(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		if (st->ways->path->name == NULL)
		{
			free(st->ways->path);
			st->ways->path = NULL;
			st->ways->path_copy = NULL;
			free(st->ways);
			st->ways = NULL;
			st->ways = st->ways_copy;
			st->ways->next = NULL;
			return ;
		}
		st->ways = st->ways->next;
	}
}

void    last_way(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways->next)
		st->ways = st->ways->next;
	st->last_way = st->ways;
}

void    last_path(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		while (st->ways->path->next)
			st->ways->path = st->ways->path->next;
		st->ways->last_path = st->ways->path;
		st->ways = st->ways->next;
	}
}

void    ways_len(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		while (st->ways->path)
		{
			st->ways->len++;
			st->ways->path = st->ways->path->next;
		}
		st->ways = st->ways->next;
	}
}

void    search_ways(t_gen *st)
{
	int     num;
	int     i;
	int     temp;
	t_ways  *prev;
	t_path  *pr;
	t_ways  *cp;

	num = path_num(st);
	if (num == 0)
	{
		printf("There is no solution\n");                          // change this
		exit(0);
	}
	while (num > 0)
	{
		if (st->ways->path->name)
		{
			st->ways->next = new_ways();
			prev = st->ways;
			st->ways = st->ways->next;
			st->ways->prev = prev;
		}
		cp = st->ways;
		i = st->first;
		set_room_busy(st, st->first, 1);
		while (i != st->last)
		{
			if ((temp = get_coor(st, i)) == -1)
			{
				clear_this_path(st, cp);
				break;
			}
			set_room_busy(st, temp, 1);
			if (st->ways->path->name)
			{
				st->ways->path->next = new_path();
				pr = st->ways->path;
				st->ways->path = st->ways->path->next;
				st->ways->path->prev = pr;
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
		set_room_busy(st, st->first, 0);
		set_room_busy(st, st->last, 0);
		num--;
	}
	check_empty_path(st);
	last_way(st);
	last_path(st);
	ways_len(st);
}
