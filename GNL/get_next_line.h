/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 12:57:11 by dlytvyn           #+#    #+#             */
/*   Updated: 2017/12/06 12:57:12 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 35
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <sys/types.h>
# include <fcntl.h>
# include "./libft/libft.h"

int					get_next_line(const int fd, char **line);

#endif
