/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:27:45 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/22 14:02:14 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_straddsizeb(char *s, size_t n)
{
	char			*new;
	size_t			size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	new = ft_strnew(size + n);
	if (!new)
		return (NULL);
	new = ft_strncpy(new, s, size);
	free(s);
	s = NULL;
	return (new);
}

static t_gnl		*ft_glstnew2(const int fd)
{
	t_gnl			*new_elem;

	new_elem = (t_gnl *)gc_malloc(sizeof(t_gnl), "gnl");
	if (!new_elem)
		return (NULL);
	new_elem->fd = fd;
	if ((new_elem->str = (char *)gc_malloc(BUFF_SIZE * BUFF_SIZE, "gnl"))
	== NULL)
		return (NULL);
	ft_bzero((void *)new_elem->str, BUFF_SIZE + 1);
	new_elem->i = 0;
	new_elem->next = NULL;
	return (new_elem);
}

static	int			ft_read_line(char **line, t_gnl *storage)
{
	int a;

	while ((a = read(storage->fd, storage->str, BUFF_SIZE)) > 0)
	{
		storage->str[a] = '\0';
		storage->i = 0;
		while (storage->str[storage->i] != '\n' && storage->str[storage->i])
			storage->i++;
		if ((*line = ft_straddsizeb(*line, storage->i)) == NULL)
			return (-1);
		*line = ft_strncat(*line, storage->str, storage->i);
		if (storage->str[storage->i] == '\n')
		{
			storage->i++;
			break ;
		}
		ft_bzero(storage->str, BUFF_SIZE + 1);
	}
	if (a <= 0 && **line == '\0')
		return (a);
	return (1);
}

static int			check_first(char **line, t_gnl *storage)
{
	int	j;

	if ((*line = ft_strnew(BUFF_SIZE)) == NULL)
		return (-1);
	if (storage->i > 0)
	{
		j = storage->i;
		while (storage->str[storage->i] != '\n' && storage->str[storage->i])
			storage->i++;
		*line = ft_strncpy(*line, storage->str + j, storage->i - j);
		if (storage->str[storage->i] == '\n')
		{
			storage->i++;
			return (1);
		}
		storage->i = 0;
	}
	return (ft_read_line(line, storage));
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*storage;
	t_gnl			*start;
	int				gg;

	if (fd < 0 || !line)
		return (-1);
	if (storage == NULL)
	{
		if ((storage = ft_glstnew2(fd)) == NULL)
			return (-1);
		return (check_first(line, storage));
	}
	start = storage;
	while (storage->fd != fd && storage->next && storage)
		storage = storage->next;
	if (storage->fd == fd)
		gg = check_first(line, storage);
	else
	{
		storage->next = ft_glstnew2(fd);
		storage = storage->next;
		gg = check_first(line, storage);
	}
	storage = start;
	return (gg);
}
