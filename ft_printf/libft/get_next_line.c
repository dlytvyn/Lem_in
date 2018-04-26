/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:20:19 by dlytvyn           #+#    #+#             */
/*   Updated: 2017/12/13 15:48:56 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*ft_realloc(void *array, size_t size)
{
	char	*res;

	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (array)
	{
		ft_strcpy(res, array);
		free(array);
	}
	return (res);
}

static	char	*ft_change(t_list *run, int i)
{
	char	*temp;

	if (((char*)run->content)[i])
	{
		temp = (char*)malloc(sizeof(char) * ft_strlen(run->content + i));
	}
	else
	{
		ft_memdel(&run->content);
		return (ft_strdup("\0"));
	}
	ft_strcpy(temp, run->content + ++i);
	if (run->content)
		ft_bzero(run->content, ft_strlen(run->content));
	ft_strdel((char**)&run->content);
	run->content = (char*)malloc(sizeof(char) * ft_strlen(temp) + 1);
	ft_strcpy(run->content, temp);
	ft_strdel(&temp);
	return (run->content);
}

static	int		is_text(t_list *run, char **line, int ret)
{
	int	i;

	i = 0;
	while (((char*)run->content)[i] && ((char*)run->content)[i] != '\n')
		i++;
	if (((char*)run->content)[i] == '\n' || ret == 0)
	{
		*line = ft_strnew(i);
		ft_strncpy(*line, run->content, i);
		run->content = ft_change(run, i);
		return (1);
	}
	else
		return (0);
}

static	t_list	*search_in_list(t_list *head, int fd)
{
	t_list	*run;

	run = head;
	while (run)
	{
		if ((int)run->content_size == fd)
		{
			return (run);
		}
		run = run->next;
	}
	while (head->next)
		head = head->next;
	head->next = ft_lstnew("\0", 1);
	head->next->content_size = fd;
	return (head->next);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*run;
	int				ret;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || read(fd, buf, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	*line = NULL;
	if (!head)
	{
		head = ft_lstnew("\0", 1);
		head->content_size = fd;
	}
	run = head;
	run = search_in_list(head, fd);
	if (((char*)run->content)[0] != '\0' && is_text(run, line, 1) == 1)
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		run->content = ft_realloc(run->content, ft_strlen(run->content) + ret);
		run->content = ft_strcat(run->content, buf);
		if (is_text(run, line, ret) == 1)
			return (1);
	}
	if (ret == 0)
		is_text(run, line, ret);
	return ((*line && *line[0]) ? 1 : 0);
}
