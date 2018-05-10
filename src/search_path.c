/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:49:49 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:49:50 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_coor(t_gen *st, int i)
{
	int		j;
	int		temp;
	int		res;

	j = 0;
	temp = get_greatest(st, i);
	res = -1;
	while (j < st->size)
	{
		if (st->matrix[i][j] != 0 && st->matrix[i][j] <= temp)
		{
			if (is_room_empty(st, j))
			{
				temp = st->matrix[i][j];
				res = j;
			}
		}
		j++;
	}
	if (res > 0)
	{
		st->matrix[i][res] = 0;
		st->matrix[res][i] = 0;
	}
	return (res);
}

void	ways_len(t_gen *st)
{
	st->ways = st->ways_copy;
	while (st->ways)
	{
		st->ways->path = st->ways->path_copy;
		while (st->ways->path)
		{
			st->ways->len++;
			st->ways->path = st->ways->path->next;
		}
		st->ways = st->ways->next;
	}
}

void    search_ways_add(t_gen *st, t_path *pr, t_ways *cp, int i)
{
	set_room_busy(st, st->first, 1);
	while (i != st->last)
	{
		if ((st->temp = get_coor(st, i)) == -1)
		{
			clear_this_path(st, cp);
			break ;
		}
		set_room_busy(st, st->temp, 1);
		if (st->ways->path->name)
		{
			st->ways->path->next = new_path();
			pr = st->ways->path;
			st->ways->path = st->ways->path->next;
			st->ways->path->prev = pr;
			st->ways->path->in = st->temp;
			st->ways->path->name = get_name(st, st->temp);
		}
		else
		{
			st->ways->path->in = st->temp;
			st->ways->path->name = get_name(st, st->temp);
		}
		i = st->temp;
	}
}

void	search_ways_add2(t_gen *st)
{
	t_ways	*prev;

	if (st->ways->path->name)
	{
		st->ways->next = new_ways();
		prev = st->ways;
		st->ways = st->ways->next;
		st->ways->prev = prev;
	}
}

void	search_ways(t_gen *st)
{
	int		i;
	t_path	*pr;
	t_ways	*cp;

	pr = NULL;
	st->num = path_num(st);
	if (st->num == 0)
		exit(0);
	while (st->num > 0)
	{
		search_ways_add2(st);
		cp = st->ways;
		i = st->first;
		search_ways_add(st, pr, cp, i);
		set_room_busy(st, st->first, 0);
		set_room_busy(st, st->last, 0);
		st->num--;
	}
	check_empty_path(st);
	st->ways = st->ways_copy;
	st->ways->path = st->ways->path_copy;
	if (st->ways->path == NULL)
		ft_error();
	last_way(st);
	last_path(st);
	ways_len(st);
}
