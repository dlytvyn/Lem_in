//
// Created by Dmytro LYTVYN on 4/4/18.
//

#include "lem_in.h"

void    set_zero(t_gen *st)
{
	int i;
	int j;

	i = 0;
	while (i < st->size)
	{
		j = 0;
		while (j < st->size)
		{
			st->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

void    create_matrix(t_gen *st)
{
	int i;

	i = 0;
	st->rooms = st->rc;
	while (st->rooms->next)
		st->rooms = st->rooms->next;
	st->size = st->rooms->index + 1;
	if (!(st->matrix = (double**)malloc(sizeof(double*) * st->size)))
		ft_error();
	while (i < st->size)
	{
		if(!(st->matrix[i] = (double*)malloc(sizeof(double) * st->size)))
			ft_error();
		i++;
	}
	set_zero(st);
}
