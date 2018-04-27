/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:47:22 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:47:24 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*new_path(void)
{
	t_path	*path;

	path = (t_path*)malloc(sizeof(t_path));
	path->in = 0;
	path->ant = 0;
	path->next = NULL;
	path->prev = NULL;
	path->name = NULL;
	return (path);
}

t_ways	*new_ways(void)
{
	t_ways	*ways;

	ways = (t_ways*)malloc(sizeof(t_ways));
	ways->path = new_path();
	ways->path_copy = ways->path;
	ways->index = 0;
	ways->len = 0;
	ways->next = NULL;
	ways->prev = NULL;
	return (ways);
}

void	ft_error(void)
{
	write(1, "Map Error\n", 10);
	exit(0);
}

t_rooms	*new_room(void)
{
	t_rooms	*elem;

	elem = (t_rooms*)malloc(sizeof(t_rooms));
	elem->x = -1;
	elem->y = -1;
	elem->name = NULL;
	elem->start = 0;
	elem->end = 0;
	elem->index = 0;
	elem->busy = 0;
	elem->ant_num = 0;
	elem->next = NULL;
	return (elem);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}
