/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:37:16 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/27 10:37:17 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		sum(t_gen *st)
{
	int	res;

	res = 0;
	st->ways = st->ways_copy;
	while (st->ways)
	{
		res += st->ways->index;
		st->ways = st->ways->next;
	}
	return (res);
}

int		real_ways(t_gen *st)
{
	int	res;

	res = 0;
	st->ways = st->ways_copy;
	while (st->ways)
	{
		res++;
		st->ways = st->ways->next;
	}
	return (res);
}
