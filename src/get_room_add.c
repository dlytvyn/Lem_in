/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:47:48 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/27 10:47:49 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_start(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms->next)
	{
		if (st->rooms->start)
			return (0);
		st->rooms = st->rooms->next;
	}
	if (st->rooms->start)
		return (0);
	return (1);
}

int		check_end(t_gen *st)
{
	st->rooms = st->rc;
	while (st->rooms->next)
	{
		if (st->rooms->end)
			return (0);
		st->rooms = st->rooms->next;
	}
	if (st->rooms->end)
		return (0);
	return (1);
}
