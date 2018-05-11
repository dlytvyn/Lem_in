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

void	show_length(t_gen *st)
{
	int i;

	i = 0;
	st->ways->path = st->ways->path_copy;
	while (st->ways->path)
	{
		i++;
		st->ways->path = st->ways->path->next;
	}
	if (st->l)
		ft_printf("{magenta}   %s %d{reset}", "|  Way's length:", i + 1);
}

void	show_ways(t_gen *st)
{
	char *name;

	ft_printf("{blue}%s\n", "All possible ways:");
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		name = get_name(st, st->first);
		ft_printf("{green}%s{reset} -> ", name);
		while (st->ways->path)
		{
			if (st->ways->path->next)
				ft_printf("{yellow}%s{reset} -> ", st->ways->path->name);
			else
				ft_printf("{red}%s{reset}", st->ways->path->name);
			st->ways->path = st->ways->path->next;
		}
		if (st->l == 1)
			show_length(st);
		ft_printf("\n");
		st->ways = st->ways->next;
		ft_strdel(&name);
	}
	ft_printf("\n");
}

void	order(t_gen *st)
{
	st->first = search_first(st);
	st->last = search_last(st);
	st->ways = new_ways();
	st->ways_copy = st->ways;
	stack_creator(st);
	empty_rooms(st);
	search_ways(st);
	define_ways(st);
	ft_printf("%s\n\n", st->map);
	if (st->w == 1)
		show_ways(st);
	motion(st);
	if (st->i == 1)
		ft_printf("\n{blue}%s: %d{reset}\n", "Number of steps", st->count_i);
	clear_all(st);
}
