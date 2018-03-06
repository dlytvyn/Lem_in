/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:30:39 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/04 14:30:39 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdlib.h>
#include "/Users/dlytvyn/Lem-in/GNL/get_next_line.h"
#include "/Users/dlytvyn/Lem-in/ft_printf/ft_printf/print.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


typedef struct      s_links
{
	int             r1;
	int             r2;
	struct s_links  *next;
}                   t_links;

typedef struct      s_rooms
{
	char            *name;
	int             start;
	int             end;
	int             x;
	int             y;
	struct s_rooms  *next;
}                   t_rooms;

typedef struct      s_st
{
	int             ants;
	t_rooms         *rooms;
	t_links         *links;
}                   t_st;

typedef struct      s_read
{
	char            *row;
	struct s_read   *next;
}                   t_read;



#endif