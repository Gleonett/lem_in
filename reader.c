/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:04:45 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/09 17:48:55 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		bufcat_and_write(char **s1, const char *s2, int flag)
{
	static int	i;
	int			j;

	if (flag == 0)
	{
		j = 0;
		while (s2[j] != '\0')
			(*s1)[i++] = s2[j++];
		(*s1)[i++] = '\n';
	}
	else
	{
		write(1, *s1, i);
		write(1, "\n", 1);
		ft_memdel((void **)s1);
	}
}

int			prep_for_read(t_th_pow_p *th_p, char **line, int *num_ants,
		int *flag)
{
	long int	b;
	int			a;

	while ((a = get_next_line(0, line)) > 0)
	{
		if (**line != '#')
			break ;
		bufcat_and_write(&(th_p->buf), *line, 0);
		ft_memdel((void **)line);
	}
	if (a < 0)
		return (1);
	IF_1_RET((a == 0 ? 1 : 0), (line), (1));
	IF_1_RET(((a = str_is_int(*line)) < 1 ? 1 : 0), (line), (1));
	if ((*line)[a] != '\0')
	{
		free(*line);
		return (1);
	}
	IF_1_RET(((b = ft_atoli(*line)) > 2147483647 || b < 1 ? 1 : 0),
			(line), (1));
	*num_ants = (int)b;
	*flag = 0;
	return (0);
}

static int	check_room(t_mtrx *mtrx, int *flag, char **line, t_th_pow_p *th_p)
{
	mtrx->total_links += 1;
	if (*flag == 0 && valid_room(*line, th_p->th, th_p->pow_p, 0) == 1)
	{
		*flag += 1;
		IF_1_RET(valid_links(th_p->th, th_p->pow_p, *line),
				line, 1);
	}
	else if (*flag != 0)
		IF_1_RET(valid_links(th_p->th, th_p->pow_p, *line),
				line, 1);
	return (0);
}

int			reader(t_th_pow_p *th_p, t_mtrx *mtrx)
{
	const int	fd = 0;
	int			flag;
	char		*line;

	th_p->buf = (char *)malloc(sizeof(char) * NUM_SMBLS);
	IF_1_RET(prep_for_read(th_p, &line, &(mtrx->num_a_r[0]), &flag), NULL, -1);
	bufcat_and_write(&(th_p->buf), line, 0);
	ft_memdel((void **)&line);
	while (get_next_line(fd, &line) > 0)
	{
		bufcat_and_write(&(th_p->buf), line, 0);
		flag == 0 ? mtrx->num_a_r[1] += 1 : 0;
		if (*line != '#')
			IF_1_RET(check_room(mtrx, &flag, &line, th_p), NULL, -1);
		if (*line == '#')
			IF_1_RET(check_comment(&line, th_p, th_p->buf, fd), &line, -1);
		ft_memdel((void **)&line);
	}
	close(fd);
	IF_1_RET(1, &line, 0);
}
