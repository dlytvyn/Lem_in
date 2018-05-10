/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 12:20:36 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/10 12:20:37 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	print_add(t_gen *st)
{
	if (st->ways->path->in == st->last)
	{
		ft_printf("{red}%s", "L");
		ft_printf("{red}%d-%s{reset}",
			st->ways->path->ant, st->ways->path->name);
	}
	else
	{
		ft_printf("{yellow}%s", "L");
		ft_printf("{yellow}%d-%s{reset}",
			st->ways->path->ant, st->ways->path->name);
	}
}

static	int		print_add2(t_gen *st, int i)
{
	if (st->ways->path->ant)
	{
		if (st->c == 1)
			print_add(st);
		else
			ft_printf("L%d-%s", st->ways->path->ant,
				st->ways->path->name);
		i++;
	}
	return (i);
}

void			print(t_gen *st)
{
	int	i;

	st->ways = st->ways_copy;
	while (st->ways)
	{
		i = 0;
		st->ways->path = st->ways->last_path;
		while (st->ways->path)
		{
			i = print_add2(st, i);
			if (st->ways->path->prev && st->ways->path->prev->ant
				&& st->ways->path->ant)
				ft_printf(" ");
			st->ways->path = st->ways->path->prev;
		}
		if (st->ways->next && i > 0)
			ft_printf(" ");
		st->ways = st->ways->next;
	}
	st->count_i++;
	ft_printf("\n");
}
