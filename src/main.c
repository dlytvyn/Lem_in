/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:48:27 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:48:30 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reader(t_gen *st)
{
	char	*line;
	int		i;

	i = 0;
	if (get_next_line(st->fd, &line) < 0)
	{
		ft_printf("Usage: ./lem-in <target file>\n");
		exit(0);
	}
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0)
			ft_error();
		i++;
	}
	st->ants = ft_atoi(line);
	st->map = ft_strdup(line);
	ft_strdel(&line);
	while (get_next_line(st->fd, &line))
	{
		line = get_data(line, st);
		add_str(st, line);
		ft_strdel(&line);
	}
}

void	flags_manager(t_gen *st, char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-f") == 0)
			st->file = 1;
		if (ft_strcmp(argv[i], "-w") == 0)
			st->w = 1;
		if (ft_strcmp(argv[i], "-c") == 0)
			st->c = 1;
		if (ft_strcmp(argv[i], "-i") == 0)
			st->i = 1;
		if (ft_strcmp(argv[i], "-l") == 0)
			st->l = 1;
		i++;
	}
}

void	initialization(t_gen *st)
{
	st->ants = 0;
	st->map = NULL;
	st->rooms = new_room();
	st->rc = st->rooms;
	st->matrix = NULL;
	st->size = 0;
	st->ways = NULL;
	st->first = 0;
	st->num = 0;
	st->last = 0;
	st->temp = 0;
	st->file = 0;
	st->w = 0;
	st->c = 0;
	st->last_way = NULL;
	st->weight = 1;
	st->i = 0;
	st->l = 1;
	st->count_i = 0;
}

int		find_file(char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-f") == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_gen	st;

	initialization(&st);
	flags_manager(&st, argv, argc);
	if (st.file == 1)
		st.fd = open(argv[find_file(argv, argc)], O_RDONLY);
	else
		st.fd = 0;
	if (st.fd < 0)
	{
		ft_printf("Usage: ./lem-in [-w -c -i -f] <target file>\n");
		exit(0);
	}
	reader(&st);
	order(&st);
}
