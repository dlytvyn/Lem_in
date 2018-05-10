/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 12:06:19 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/10 12:06:20 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_ways(t_gen *st)
{
	t_path *tmp_p;
	t_ways *tmp_w;

	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		while (st->ways->path)
		{
			tmp_p = st->ways->path->next;
			ft_strdel(&st->ways->path->name);
			free(st->ways->path);
			st->ways->path = tmp_p;
		}
		tmp_w = st->ways->next;
		free(st->ways);
		st->ways = tmp_w;
	}
}

void	clear_rooms(t_gen *st)
{
	t_rooms *tmp;

	st->rooms = st->rc;
	while (st->rooms)
	{
		tmp = st->rooms->next;
		ft_strdel(&st->rooms->name);
		free(st->rooms);
		st->rooms = tmp;
	}
}

void	clear_all(t_gen *st)
{
	int i;

	i = 0;
	ft_strdel(&st->map);
	while (i < st->size)
		free(st->matrix[i++]);
	free(st->matrix);
	st->matrix = NULL;
	clear_ways(st);
	clear_rooms(st);
}
