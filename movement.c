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
		st->ways->path = st->ways->path->prev;
	}
	return (finish);
}

void    print(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->last_path;
		while (st->ways->path)
		{
			if (st->ways->path->ant)
				printf("L%d-%s", st->ways->path->ant, st->ways->path->name);                                             // change it
			if (st->ways->path->prev && st->ways->path->ant)
				printf(" ");
			st->ways->path = st->ways->path->prev;
		}
		if (st->ways->next)
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

void    define_ways(t_gen *st)
{
	while (sum(st) < st->ants)
	{
		st->ways = st->last_way;
		while (st->ways->prev)
		{
			if ((st->ways->prev->index - st->ways->index) >= (st->ways->len - st->ways->prev->len))
			{
				st->ways->index++;
				break ;
			}
			else
				st->ways = st->ways->prev;
			if (st->ways->prev == NULL)
			{
				st->ways->index++;
				break ;
			}
		}
	}
}