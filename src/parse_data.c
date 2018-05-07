/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:49:18 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:49:19 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#include "stdio.h"

void	check_basic(t_gen *st)
{
	int start;
	int end;

	start = 0;
	end = 0;
	st->rooms = st->rc;
	while (st->rooms)
	{
		if (st->rooms->start == 1)
			start++;
		else if (st->rooms->end == 1)
			end++;
		st->rooms = st->rooms->next;
	}
	if (start != 1 || end != 1)
	{
		ft_printf("No start or no end\n");
		ft_error();
	}
}

char	*get_data(char *line, t_gen *st)
{
	if (line[0] == '#' && ft_strcmp(line, "##start") != 0
		&& ft_strcmp(line, "##end") != 0)
	{
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		line = get_data(line, st);
		return (line);
	}
	if (ft_strchr(line, '-'))
	{
		check_basic(st);
		if (st->matrix == NULL)
			create_matrix(st);
		line = get_link_data(line, st);
	}
	else
		line = get_room_data(line, st);
	return (line);
}
