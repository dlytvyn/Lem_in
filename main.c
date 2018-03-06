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

t_links *new_links()
{
	t_links *links;

	links = (t_links*)malloc(sizeof(t_links));
	links->r1 = 0;
	links->r2 = 0;
	links->next = NULL;
	return (links);
}

t_rooms *new_rooms()
{
	t_rooms *rooms;

	rooms = (t_rooms*)malloc(sizeof(t_rooms));
	rooms->end = 0;
	rooms->next = 0;
	rooms->name = NULL;
	rooms->x = 0;
	rooms->y = 0;
	rooms->next = 0;
	return (rooms);
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

int     is_room_valid(char *row)
{
	int i;

	i = 0;
	while (row[i] != ' ')
		i++;
	while (row[i])
	{
		if (ft_isdigit(row[i]) == 1 || row[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
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
	int i;

	i = 0;
	if (!is_room_valid(run->row))
		exit(1);
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

int     is_valid_link(char *str)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		else if (str[i] == '-')
			c++;
		i++;
		if (c > 1)
			return (0);
	}
	return (1);
}

void    get_link_data(t_read *run, t_st *st)
{
	int i;

	if (!is_valid_link(run->row))
		exit (1);
	i = 0;
	st->links->r1 = ft_atoi(run->row);
	while (run->row[i] != '-')
		i++;
	i++;
	st->links->r2 = ft_atoi(run->row + i);
}

void    get_data(t_read *run, t_st *st)
{
	st->ants = ft_atoi(run->row);
	if (st->ants <= 0)
		exit(1);
	run = run->next;
	while (run)
	{
		if (ft_strstr(run->row, "-") == 0)
		{
			if (st->rooms->name != NULL)
			{
				st->rooms->next = new_rooms();
				st->rooms = st->rooms->next;
			}
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
			else
				get_room_data(run, st);
			run = run->next;
		}
		else if (ft_strstr(run->row, "-") != 0)
		{
			if (st->links->r1 != 0 || st->links->r2 != 0)
			{
				st->links->next = new_links();
				st->links = st->links->next;
			}
			get_link_data(run, st);
			run = run->next;
		}
		else if (ft_strcmp(run->row, "#comment"))
			run = run->next;
		else
			exit (1);
	}
}

t_st    *new_st()
{
	t_st    *st;

	st = (t_st*)malloc(sizeof(t_st));
	st->ants = 0;
	st->links = new_links();
	st->rooms = new_rooms();
	return (st);
}

int main()
{
	t_read  *field;
	t_st    *st;
	int     fd;

	field = new_lst();
	st = new_st();
	fd = open("/Users/dlytvyn/Lem-in/test/2.txt", O_RDONLY);
	read_field(field, fd);
	get_data(field, st);
	print_res(field);
}