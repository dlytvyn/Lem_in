/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:30:57 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/04 14:30:58 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_read  *new_lst()
{
	t_read *run;

	run = (t_read*)malloc(sizeof(t_read));
	run->row = NULL;
	run->next = NULL;
	return (run);
}

void read_field(t_read *field, int fd)
{
	char *line;

	if (get_next_line(fd, &line))
	{
		field->row = ft_strdup(line);
		ft_strdel(&line);
	}
	while (get_next_line(fd, &line))
	{
		field->next = new_lst();
		field = field->next;
		field->row = ft_strdup(line);
		ft_strdel(&line);
	}
}

void    print_res(t_read *run)
{
	while (run)
	{
		printf("%s\n", run->row);
		run = run->next;
	}
}

void    get_room_data(t_read *run, t_st *st)
{
	int     i;

	i = 0;
	while (run->row[i] != ' ')
		i++;
	st->rooms->name = ft_strnew(i + 1);
	ft_strncpy(st->rooms->name, run->row, i);
	i++;
	st->rooms->x = ft_atoi(run->row + i);
	while (run->row[i] != ' ')
		i++;
	st->rooms->y = ft_atoi(run->row + i);
}

int     is_data_valid(char *row)
{
	int i;

	i = 0;
	while (row[i])
	{

	}
}

void    get_data(t_read *run, t_st *st)
{
	st->ants = ft_atoi(run->row);
	if (st->ants <= 0)
		exit(1);
	run = run->next;
	while (run)
	{
		if (ft_strcmp(run->row, "##start") == 0)
		{
			run = run->next;
			st->rooms->start = 1;
			get_room_data(run, st);
		}
		else if (ft_strcmp(run->row, "##end") == 0)
		{
			run = run->next;
			st->rooms->end = 1;
			get_room_data(run, st);
		}
		else if ()
		run = run->next;
	}
}

t_st    *new_st()
{
	t_st    *st;

	st = (t_st*)malloc(sizeof(t_st));
	st->ants = 0;
	st->links = (t_links*)malloc(sizeof(t_links));
	st->links->r1 = 0;
	st->links->r2 = 0;
	st->links->next = NULL;
	st->rooms = (t_rooms*)malloc(sizeof(t_rooms));
	st->rooms->end = 1;
	st->rooms->next = 0;
	st->rooms->name = NULL;
	st->rooms->x = 0;
	st->rooms->y = 0;
	st->rooms->next = 0;
	return (st);
}

int main()
{
	t_read  *field;
	t_st    *st;
	int     fd;

	field = new_lst();
	st = new_st();
	fd = open("/Users/dlytvyn/Lem-in/map", O_RDONLY);
	read_field(field, fd);
	get_data(field, st);
	print_res(field);
}