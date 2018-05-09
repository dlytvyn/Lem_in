/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:49:06 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:49:07 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		move_path(t_gen *st, int finish)
{
	st->ways->path = st->ways->last_path;
	if (!st->ways->path->prev)
	{
		if (st->ways->path->in == st->last && st->ways->path->ant)
		{
			st->ways->path->ant = 0;
			finish++;
		}
	}
	while (st->ways->path->prev)
	{
		if (st->ways->path == st->ways->last_path && st->ways->path->ant)
			finish++;
		st->ways->path->ant = st->ways->path->prev->ant;
		st->ways->path->prev->ant = 0;
		st->ways->path = st->ways->path->prev;
	}
	return (finish);
}

void	print_add(t_gen *st)
{
	if (st->ways->path->in == st->last)
	{
		ft_printf("{red}%s", "L");
		ft_printf("{red}%d-%s{reset}", st->ways->path->ant, st->ways->path->name);
	}
	else
	{
		ft_printf("{yellow}%s", "L");
		ft_printf("{yellow}%d-%s{reset}", st->ways->path->ant, st->ways->path->name);
	}
}

void	print(t_gen *st)
{
	int	i;

	st->ways = st->ways_copy;
	while (st->ways)
	{
		i = 0;
		st->ways->path = st->ways->last_path;
		while (st->ways->path)
		{
			if (st->ways->path->ant)
			{
				if (st->c == 1)
					print_add(st);
				else
					ft_printf("L%d-%s", st->ways->path->ant, st->ways->path->name);
				i++;
			}
			if (st->ways->path->prev && st->ways->path->prev->ant
				&& st->ways->path->ant)
				ft_printf(" ");
			st->ways->path = st->ways->path->prev;
		}
		if (st->ways->next && i > 0)
			ft_printf(" ");
		st->ways = st->ways->next;
	}
	ft_printf("\n");
}

void	motion(t_gen *st)
{
	int	count;
	int	finish;

	count = 1;
	finish = 0;
	while (finish < st->ants)
	{
		st->ways = st->ways_copy;
		while (st->ways)
		{
			finish = move_path(st, finish);
			if (st->ways->index)
			{
				st->ways->path->ant = count;
				count++;
				st->ways->index--;
			}
			st->ways = st->ways->next;
		}
		if (finish == st->ants)
			return ;
		print(st);
	}
}

void	helping(t_gen *st)
{
	st->ways = st->ways_copy;
	st->ways->index = st->ants;
}

void	define_ways(t_gen *st)
{
	while (sum(st) < st->ants)
	{
		if (real_ways(st) > 1)
		{
			st->ways = st->last_way;
			while (st->ways->prev)
			{
				if ((st->ways->prev->index - st->ways->index) >=
					(st->ways->len - st->ways->prev->len))
				{
					st->ways->index++;
					break ;
				}
				else
					st->ways = st->ways->prev;
				if (st->ways->prev == NULL)
				{
					st->ways->index++;
					break ;
				}
			}
		}
		else
			helping(st);
	}
}
