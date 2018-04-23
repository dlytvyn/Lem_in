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
	return (0);
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
	return (0);
}

int     path_num(t_gen *st)
{
	int j;
	int res;

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

int     room_in_stack(int *stack, int j)
{
	int i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == j)
			return  (1);
		i++;
	}
	return (0);
}

int     *search_elem(t_gen *st, int* stack, int row)
{
	int j;
	int k;

	j = 0;
	while (j < st->size)
	{
		if (st->matrix[row][j] == 1 && is_room_empty(st, j))
		{
			if (!room_in_stack(stack, j))
			{
				k = 0;
				while (k < st->size && stack[k] != -1)
					k++;
				stack[k] = j;
			}
			st->matrix[row][j] = st->weight;
			st->matrix[j][row] = st->weight;
		}
		j++;
	}
	return (stack);
}

int     *set_stack(t_gen *st, int *stack)
{
	int i;

	i = 0;
	while (i < st->size)
	{
		stack[i] = -1;
		i++;
	}
	return (stack);
}

int     get_greatest(t_gen *st, int i)
{
	int j;
	int res;

	j = 0;
	res = 0;
	while (j < st->size)
	{
		if (st->matrix[i][j] > res)
			res = st->matrix[i][j];
		j++;
	}
	return (res);
}

void    stack_creator(t_gen *st)
{
	int     *stack;
	int     k;
	int     i;

	k = 0;
	stack = (int*)malloc(sizeof(int) * st->size);
	i = st->last;
	stack = set_stack(st, stack);
	stack[k] = st->last;
	while (k < st->size)
	{
		stack = search_elem(st, stack, stack[k]);
		set_room_busy(st, stack[k], 1);
		st->weight = get_greatest(st, k) + 1;
		k++;
	}
}

void    empty_rooms(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		st->rooms->busy = 0;
		st->rooms = st->rooms->next;
	}
}

void    order(t_gen *st)
{
	st->first = search_first(st);
	st->last = search_last(st);
	st->ways = new_ways();
	st->ways_copy = st->ways;
	stack_creator(st);
	empty_rooms(st);
	search_ways(st);
	define_ways(st);
	printf("%s\n\n", st->map);
	motion(st);

	int i = 0;
	int j = 0;
	while  (i < st->size)
	{
		j = 0;
		while (j <st->size)
		{
			printf("%f ", st->matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}