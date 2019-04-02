/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 17:31:09 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/20 17:48:36 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int g_fd;

static int	check_comment_2(char **line, t_tbhash **th, size_t pow_p[], int num)
{
	ft_memdel((void **)line);
	if (th[NUM_ROOMS - num] == NULL && get_next_line(g_fd, line) > 0)
	{
		if (valid_room(*line, th, pow_p, num))
			return (1);
	}
	else
		return (1);
	return (0);
}

int			check_comment(char **line, t_tbhash **th, size_t pow_p[], int fd)
{
	int i;

	(*line)[2] == 's' ? i = 7 : 0;
	(*line)[2] == 'e' ? i = 5 : 0;
	(*line)[2] != 'e' && (*line)[2] != 's' ? i = 0 : 0;
	g_fd = fd;
	if (ft_strncmp(*line, "##start", (size_t)i) == 0 && skip_spaces(*line, &i)
			== 1)
	{
		if (check_comment_2(line, th, pow_p, 2) == 1)
			return (1);
	}
	else if (ft_strncmp(*line, "##end", (size_t)i) == 0 &&
		skip_spaces(*line, &i) == 1)
	{
		if (check_comment_2(line, th, pow_p, 1) == 1)
			return (1);
	}
	return (0);
}
