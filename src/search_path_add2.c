/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_add2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:45:17 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/27 11:45:18 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_this_path(t_gen *st, t_ways *cp)
{
	t_path *tmp;

	st->ways = cp;
	st->ways->path = st->ways->path_copy;
	while (st->ways->path)
	{
		tmp = st->ways->path->next;
		if (st->ways->path)
			set_room_busy(st, st->ways->path->in, 0);
		if (st->ways->path->name)
			ft_strdel(&st->ways->path->name);
		free(st->ways->path);
		st->ways->path = tmp;
	}
	st->ways->path = new_path();
	st->ways->path_copy = st->ways->path;
}

void	check_empty_path(t_gen *st)
{
	t_ways *tmp;

	tmp = NULL;
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
			if (tmp)
				tmp->next = NULL;
			return ;
		}
		tmp = st->ways;
		st->ways = st->ways->next;
	}
}
