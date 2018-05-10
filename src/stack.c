/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 12:08:30 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/10 12:08:31 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
