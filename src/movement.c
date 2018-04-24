//
// Created by Dmytro LYTVYN on 4/20/18.
//

#include "lem_in.h"


#include <stdio.h>

int     move_path(t_gen *st, int finish)
{
	st->ways->path = st->ways->last_path;
	while (st->ways->path->prev)
	{
		if (st->ways->path == st->ways->last_path && st->ways->path->ant)
			finish++;
		st->ways->path->ant = st->ways->path->prev->ant;
		st->ways->path->prev->ant = 0;
		st->ways->path = st->ways->path->prev;
	}
	return (finish);
}

void    print(t_gen *st)
{
	int i;

	st->ways = st->ways_copy;
	while (st->ways)
	{
		i = 0;
		st->ways->path = st->ways->last_path;
		while (st->ways->path)
		{
			if (st->ways->path->ant)
			{
				printf("L%d-%s", st->ways->path->ant, st->ways->path->name);                                           // change this
				i++;
			}
			if (st->ways->path->prev && st->ways->path->prev->ant && st->ways->path->ant)
				printf(" ");
			st->ways->path = st->ways->path->prev;
		}
		if (st->ways->next && i > 0)
			printf(" ");
		st->ways = st->ways->next;
	}
	printf("\n");
}

void    motion(t_gen *st)
{
	int count;
	int finish;

	count = 1;
	finish = 0;
	while (finish < st->ants)
	{
		st->ways = st->ways_copy;
		while (st->ways)
		{
			finish = move_path(st, finish);
			if (st->ways->index)
			{
				st->ways->path->ant = count;
				count++;
				st->ways->index--;
			}
			st->ways = st->ways->next;
		}
		if (finish == st->ants)
			return ;
		print(st);
	}
}

int     sum(t_gen *st)
{
	int res;

	res = 0;
	st->ways = st->ways_copy;
	while (st->ways)
	{
		res += st->ways->index;
		st->ways = st->ways->next;
	}
	return (res);
}

int     real_ways(t_gen *st)
{
	int res;

	res = 0;
	st->ways = st->ways_copy;
	while (st->ways)
	{
		res++;
		st->ways = st->ways->next;
	}
	return (res);
}

void    define_ways(t_gen *st)
{
	while (sum(st) < st->ants)
	{
		if (real_ways(st) > 1)
		{
			st->ways = st->last_way;
			while (st->ways->prev)
			{
				if ((st->ways->prev->index - st->ways->index) >= (st->ways->len - st->ways->prev->len))
				{
					st->ways->index++;
					break;
				}
				else
					st->ways = st->ways->prev;
				if (st->ways->prev == NULL)
				{
					st->ways->index++;
					break;
				}
			}
		}
		else
		{
			st->ways = st->ways_copy;
			st->ways->index = st->ants;
		}
	}
}