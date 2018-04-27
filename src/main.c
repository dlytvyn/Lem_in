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

int		main(int argc, char **argv)
{
	t_gen	st;

	if (argc != 2)
		return (1);
	st.fd = open(argv[1], O_RDONLY);
	if (st.fd < 0)
	{
		ft_printf("Usage: ./lem-in <target file>\n");
		exit(0);
	}
	st.ants = 0;
	st.map = NULL;
	st.rooms = new_room();
	st.rc = st.rooms;
	st.matrix = NULL;
	st.size = 0;
	st.ways = NULL;
	st.first = 0;
	st.num = 0;
	st.last = 0;
	st.temp = 0;
	st.last_way = NULL;
	st.weight = 1;
	reader(&st);
	order(&st);
}
