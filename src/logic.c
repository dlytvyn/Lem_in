/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:48:12 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:48:13 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*search_elem(t_gen *st, int *stack, int row)
{
	int	j;
	int	k;

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

int		*set_stack(t_gen *st, int *stack)
{
	int	i;

	i = 0;
	while (i < st->size)
	{
		stack[i] = -1;
		i++;
	}
	return (stack);
}

int		room_in_stack(int *stack, int j)
{
	int	i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == j)
			return (1);
		i++;
	}
	return (0);
}

void	stack_creator(t_gen *st)
{
	int	*stack;
	int	k;

	k = 0;
	stack = (int*)malloc(sizeof(int) * st->size);
	stack = set_stack(st, stack);
	stack[k] = st->last;
	while (k < st->size)
	{
		if (stack[k] == -1)
			break ;
		stack = search_elem(st, stack, stack[k]);
		set_room_busy(st, stack[k], 1);
		st->weight += 1;
		k++;
	}
	free(stack);
}

void    show_ways(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		ft_printf("{green}%s{reset} -> ", get_name(st, st->first));
		while (st->ways->path)
		{
			ft_printf("%s", st->ways->path->name);
			if (st->ways->path->next)
				ft_printf(" -> ");
			else
				ft_printf("{red}%s{reset} -> ", st->ways->path->name);
			st->ways->path = st->ways->path->next;
		}
		st->ways = st->ways->next;
	}
}

void	order(t_gen *st)
{
	st->first = search_first(st);
	st->last = search_last(st);
	st->ways = new_ways();
	st->ways_copy = st->ways;
	stack_creator(st);
	//pr_map(st);
	empty_rooms(st);
	search_ways(st);
	define_ways(st);
	ft_printf("%s\n\n", st->map);
	if (st->w == 1)
		show_ways(st);
	motion(st);
}
