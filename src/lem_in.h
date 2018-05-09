/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:03:30 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/04/26 13:03:31 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../ft_printf/src/print.h"

typedef struct		s_rooms
{
	char			*name;
	int				x;
	int				y;
	int				start;
	int				end;
	int				index;
	int				busy;
	int				ant_num;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_path
{
	int				in;
	char			*name;
	int				ant;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_ways
{
	struct s_path	*path;
	struct s_path	*path_copy;
	struct s_path	*last_path;
	int				index;
	int				len;
	struct s_ways	*prev;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_gen
{
	int				fd;
	int				ants;
	char			*map;
	struct s_rooms	*rooms;
	struct s_rooms	*rc;
	int			    **matrix;
	int				size;
	struct s_ways	*ways;
	struct s_ways	*ways_copy;
	int				first;
	int				last;
	int				weight;
	int				num;
	int				temp;
	int             file;
	int             w;
	int				c;
	struct s_ways	*last_way;
}					t_gen;

t_rooms				*new_room();
void				add_str(t_gen *st, char *line);
int					array_len(char **array);
void				free_array(char **array);
char				*get_data(char *line, t_gen *st);
void				create_matrix(t_gen *st);
void				ft_error(void);
char				*get_room_data(char *line, t_gen *st);
char				*get_link_data(char *line, t_gen *st);
void				order(t_gen *st);
t_ways				*new_ways(void);
t_path				*new_path(void);
void				search_ways(t_gen *st);
int					path_num(t_gen *st);
void				define_ways(t_gen *st);
void				motion(t_gen *st);
void				set_room_busy(t_gen *st, int room, int busy);
int					is_room_empty(t_gen *st, int room);
int					get_greatest(t_gen *st, int i);
int					room_in_stack(int *stack, int j);
int					search_last(t_gen *st);
int					search_first(t_gen *st);
void				empty_rooms(t_gen *st);
int					sum(t_gen *st);
int					real_ways(t_gen *st);
char				*get_name(t_gen *st, int room);
void				last_way(t_gen *st);
void				last_path(t_gen *st);
int					check_end(t_gen *st);
int					check_start(t_gen *st);
void				clear_this_path(t_gen *st, t_ways *cp);
void				check_empty_path(t_gen *st);


void    pr_map(t_gen *st);

#endif
