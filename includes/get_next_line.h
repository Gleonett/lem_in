/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:29:04 by gleonett          #+#    #+#             */
/*   Updated: 2018/12/12 16:56:29 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 128

# include <stdio.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

int					get_next_line(const int fd, char **line);

typedef	struct		s_gnl
{
	int				fd;
	char			*str;
	int				i;
	struct s_gnl	*next;
}					t_gnl;

#endif
