/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:47:59 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:48:00 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_room(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] != ' ')
	{
		ft_printf("Check room 1\n");
		ft_error();

	}
	else
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	if (line[i] != ' ')
	{
		ft_printf("Check room 2\n");
		ft_error();

	}
	else
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}

int		check_same_coor(t_gen *st, int x, int y)
{
	st->rooms = st->rc;
	while (st->rooms->next)
	{
		if (st->rooms->x == x && st->rooms->y == y)
			return (0);
		st->rooms = st->rooms->next;
	}
	if (st->rooms->x == x && st->rooms->y == y)
		return (0);
	return (1);
}

char	*get_room_data_add(char *line, t_gen *st)
{
	if (ft_strcmp(line, "##start") == 0)
	{
		if (!check_start(st))
		{
			ft_printf("one more start\n");
			ft_error();

		}
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		st->rooms->start = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (!check_end(st))
		{
			ft_printf("one more end\n");
			ft_error();

		}
		add_str(st, line);
		ft_strdel(&line);
		get_next_line(st->fd, &line);
		st->rooms->end = 1;
	}
	return (line);
}

char	*get_room_data(char *line, t_gen *st)
{
	char **array;

	if (st->rooms->name != NULL)
	{
		st->rooms->next = new_room();
		st->rooms->next->index = st->rooms->index + 1;
		st->rooms = st->rooms->next;
	}
	line = get_room_data_add(line, st);
	if (check_room(line) == 0)
	{
		ft_printf("checking room\n");
		ft_error();
	}
	array = ft_strsplit(line, ' ');
	if (array_len(array) != 3)
	{
		ft_printf("array len is not 3\n");
		ft_error();
	}
	if (!check_same_coor(st, ft_atoi(array[1]), ft_atoi(array[2])))
	{
		ft_printf("same coordinates\n");
		ft_error();
	}
	st->rooms->name = ft_strdup(array[0]);
	st->rooms->x = ft_atoi(array[1]);
	st->rooms->y = ft_atoi(array[2]);
	free_array(array);
	return (line);
}
