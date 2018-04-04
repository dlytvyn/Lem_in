//
// Created by Dmytro LYTVYN on 4/3/18.
//

#include "lem_in.h"

#include <stdio.h>

void    reader(t_gen *st)
{
	char    *line;
	int     i;

	i = 0;
	get_next_line(st->fd, &line);
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
		get_data(line, st);
		add_str(st, line);
		ft_strdel(&line);
	}
}

int main(int argc, char **argv)
{
	t_gen   st;
	if (argc != 2)
		return (1);
	st.fd = open(argv[1], O_RDONLY);
	st.ants = 0;
	st.rooms = new_room();
	st.rc = st.rooms;
	st.matrix = NULL;
	st.size = 0;
	st.ways = NULL;
	st.first = 0;
	st.last = 0;
	reader(&st);
	order(&st);

}
