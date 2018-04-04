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
	struct s_rooms  *next;

}                   t_rooms;

typedef struct      s_path
{
	int             in;
	struct  s_path  *next;
}                   t_path;

typedef struct      s_ways
{
	struct s_path   *path;
	struct s_ways   *next;
}                   t_ways;

typedef struct      s_gen
{
	int             fd;
	int             ants;
	char            *map;
	struct  s_rooms *rooms;
	struct  s_rooms *rc;
	int             **matrix;
	int             size;
}                   t_gen;

t_rooms *new_room();
void    add_str(t_gen *st, char *line);
int     array_len(char **array);
void    free_array(char **array);
void    get_data(char *line, t_gen *st);
void    create_matrix(t_gen *st);
void    ft_error(void);
void    get_room_data(char *line, t_gen *st);
void    get_link_data(char *line, t_gen *st);

#endif //LEM_IN_LEM_IN_H
