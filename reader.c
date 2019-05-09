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

int	skip_spaces(const char *str, int *i)
{
	while (str[*i] && (str[*i] == '\t' || str[*i] == ' '))
		*i += 1;
	return (str[*i] == '\0' ? 1 : 0);
}

int	str_is_int(const char *str)
{
	int i;
	int j;

	i = 0;
	if (skip_spaces(str, &i) == 1)
		return (-1);
	j = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i - j > 12 || ((str[j] == '+' || str[j] == '-') &&
		(i - j == 1)))
		return (0);
	else if (str[j] == '-')
		return (i * -1);
	return (i);
}

int	prep_for_read(int fd, char **line, int *num_ants, int *flag)
{
	long int	b;
	int			a;

	while ((a = get_next_line(fd, line)) > 0)
	{
		if (**line != '#')
			break ;
		ft_memdel((void **)line);
	}
	if (a < 0)
		return (1);
	IF_TRUE_RET((a == 0 ? 1 : 0), (line), (1));
	IF_TRUE_RET((str_is_int(*line) < 1 ? 1 : 0), (line), (1));
	IF_TRUE_RET(((b = ft_atoli(*line)) > 2147483647 || b < -2147483648 ? 1 : 0),
			(line), (1));
	*num_ants = (int)b;
	ft_memdel((void **)line);
	*flag = 0;
	return (0);
}

int	reader(t_tbhash **th, size_t *pow_p, t_mtrx *mtrx)
{
	int			flag;
	char		*line;
	const int	fd = open(MAP, O_RDONLY);

	if (prep_for_read(fd, &line, &(mtrx->num_a_r[0]), &flag) == 1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		flag == 0 ? mtrx->num_a_r[1] += 1 : 0;
		if (*line != '#')
		{
			mtrx->total_links += 1;
			if (flag == 0 && valid_room(line, th, pow_p, 0) == 1)
			{
				flag++;
//				mtrx->mtrx = init_mtrx(mtrx->num_a_r[1]);
				IF_TRUE_RET(valid_links(th, pow_p, line, mtrx->ways),
						&line, -1);
			}
			else if (flag != 0)
				IF_TRUE_RET(valid_links(th, pow_p, line, mtrx->ways),
						&line, -1);
		}
		else
			IF_TRUE_RET(check_comment(&line, th, pow_p, fd), &line, -1);
		ft_memdel((void **)&line);
	}
	close(fd);
	ft_memdel((void **)&line);
	return (0);
}
