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
		if (st->rooms->start == 1)
			return (st->rooms->index);
		st->rooms = st->rooms->next;
	}
}

int     search_last(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->end == 1)
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
		if (st->matrix[st->first][j])
			res++;
		j++;
	}
	return (res);
}

int     check_coor(t_gen *st, int j, int index)
{
	st->ways = st->ways_copy;
	while (st->ways && st->ways->index <= index)
	{
		st->ways->path = st->ways->path_copy;
		while (st->ways->path)
		{
			if (j == st->ways->path->in)
			{
				while (st->ways->index != index)
				{
					while (st->ways->path->next)
						st->ways->path = st->ways->path->next;
					st->ways = st->ways->next;
				}
				return (0);
			}
			if (st->ways->path->next == NULL)
				return (1);
			st->ways->path = st->ways->path->next;
		}
		st->ways = st->ways_copy->next;
	}
	return (1);
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
			if (check_coor(st, j, st->ways->index) == 1)
			{
				st->ways->path->next = new_path();
				st->ways->path = st->ways->path->next;
				st->ways->path->in = j;
				break;
			}
		}
		j++;
	}
	i = st->ways->path->in;
	while (i < st->size)
	{
		(i == st->first) ? i++ : i;
		j = 0;
		while (j < st->size)
		{
			if (st->matrix[i][j] == 1)
			{
				if (check_coor(st, j, st->ways->index) == 1)
				{
					st->ways->path->next = new_path();
					st->ways->path = st->ways->path->next;
					st->ways->path->in = j;
					i = st->ways->path->in;
					break;
				}
				else if (st->ways->path->in == st->last)
					return ;
			}
			if (j == st->size - 1)
				i++;
			j++;
		}

	}
}



double  search_greatest(t_gen *st, int i)
{
	int j;
	double res;

	j = 0;
	res = 0;
	while (j < st->size)
	{
		if (st->matrix[i][j] != 1 && st->matrix[i][j] > res)
			res = st->matrix[i][j];
		j++;
	}
	return (res);
}

void    check_next(double coef, t_gen *st, int i)
{
	int j;

	j = 0;
	coef = search_greatest(st, i) * 0.8;

	while (j < st->size)
	{
		if (st->matrix[i][j] == 1)
		{
			st->matrix[i][j] = coef;
			st->matrix[j][i] = coef;
		}
		j++;
	}
}

void    set_feromons(t_gen *st)
{
	int i;
	int j;
	double coef;
	int flag;

	flag = 0;
	coef = 0.8;
	i = st->last;
	while (i < st->size)
	{
		j = 0;
		while (j < st->size)
		{
			if (st->matrix[i][j])
			{
				if (flag == 0)
				{
					st->matrix[i][j] = coef;
					st->matrix[j][i] = coef;
				}
				check_next(coef, st, j);
			}
			j++;
		}
		if (flag == 0)
			i = 0;
		else
			i++;
		flag = 1;
		if (i == st->last)
			i++;
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
		st->ways->next->index = st->ways->index + 1;
		st->ways = st->ways->next;
		i++;
	}
	st->ways = st->ways_copy;
//	while (st->ways)
//	{
//		search_path(st);
//		st->ways = st->ways->next;
//	}



	set_feromons(st);
	search_ways(st);
	st->ways = st->ways_copy;
	i = 0;
	int j = 0;
	printf("\n");
	while (i < st->size)
	{
		j = 0;
		while (j < st->size)
		{
			printf("%f ", st->matrix[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}