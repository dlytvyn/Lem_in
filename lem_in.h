//
// Created by Dmytro LYTVYN on 4/3/18.
//

#ifndef LEM_IN_H
#define LEM_IN_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "ft_printf/libft/libft.h"
# include "GNL/get_next_line.h"

typedef struct      s_rooms
{
	char            *name;
	int             x;
	int             y;
	int             start;
	int             end;
	int             index;
	int             busy;
	int             ant_num;
	struct s_rooms  *next;

}                   t_rooms;

typedef struct      s_path
{
	int             in;
	char            *name;
	int             ant;
	struct  s_path  *next;
	struct  s_path  *prev;
}                   t_path;

typedef struct      s_ways
{
	struct s_path   *path;
	struct s_path   *path_copy;
	struct s_path   *last_path;
	int             index;
	int             len;
	struct s_ways   *prev;
	struct s_ways   *next;
}                   t_ways;

typedef struct      s_gen
{
	int             fd;
	int             ants;
	char            *map;
	struct  s_rooms *rooms;
	struct  s_rooms *rc;
	double          **matrix;
	int             size;
	struct  s_ways  *ways;
	struct s_ways   *ways_copy;
	int             first;
	int             last;
	int             weight;
	struct s_ways   *last_way;
}                   t_gen;

t_rooms *new_room();
void    add_str(t_gen *st, char *line);
int     array_len(char **array);
void    free_array(char **array);
char    *get_data(char *line, t_gen *st);
void    create_matrix(t_gen *st);
void    ft_error(void);
char    *get_room_data(char *line, t_gen *st);
char    *get_link_data(char *line, t_gen *st);
void    order(t_gen *st);
t_ways  *new_ways(void);
t_path  *new_path(void);
void    search_ways(t_gen *st);
int     path_num(t_gen *st);
void    define_ways(t_gen *st);
void    motion(t_gen *st);
void    set_room_busy(t_gen *st, int room, int busy);
int     is_room_empty(t_gen *st, int room);
int     get_greatest(t_gen *st, int i);

#endif //LEM_IN_LEM_IN_H
