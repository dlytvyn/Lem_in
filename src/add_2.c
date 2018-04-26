/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:52:40 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 12:52:41 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_str(t_gen *st, char *line)
{
	char	*tmp;

	tmp = ft_strdup(st->map);
	ft_strdel(&st->map);
	st->map = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	tmp = ft_strdup(st->map);
	ft_strdel(&st->map);
	st->map = ft_strjoin(tmp, line);
	ft_strdel(&tmp);
}

int		array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
