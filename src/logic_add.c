/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:08:19 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 13:08:20 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		search_first(t_gen *st)
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

int		search_last(t_gen *st)
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

int		path_num(t_gen *st)
{
	int	j;
	int	res;

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

void	empty_rooms(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		st->rooms->busy = 0;
		st->rooms = st->rooms->next;
	}
}

int		get_greatest(t_gen *st, int i)
{
	int	j;
	int	res;

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
