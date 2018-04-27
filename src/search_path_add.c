/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:33:40 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/27 10:33:41 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*get_name(t_gen *st, int room)
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

void	set_room_busy(t_gen *st, int room, int busy)
{
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->index == room)
			st->rooms->busy = (busy == 1) ? 1 : 0;
		st->rooms = st->rooms->next;
	}
}

int		is_room_empty(t_gen *st, int room)
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

void	last_way(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways->next)
		st->ways = st->ways->next;
	st->last_way = st->ways;
}

void	last_path(t_gen *st)
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
