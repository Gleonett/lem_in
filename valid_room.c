/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 13:59:42 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/17 16:56:01 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*get_room(char const *s, int i)
{
	int		j;
	char	*room;

	CH_NULL(room = (char *)malloc(sizeof(char) * i));
	j = -1;
	while (++j < i - 1)
		room[j] = s[j];
	room[j] = '\0';
	return (room);
}

static int	check_and_hash(t_tbhash *room, char const *s, size_t pow_p[])
{
	int		i;
	int		buf;
	size_t	h;

	i = -1;
	h = 0;
	while (s[++i] > ' ' && s[i] < 127 && s[i])
		if (i < SIZE_POW)
			h += (s[i] * pow_p[i]);
		else
			h += (s[i] * power_p_more(pow_p[SIZE_POW - 1], (size_t)i));
	if (s[i++] != ' ')
		return (-1);
	room->room = get_room(s, i);
	if (room->place_mtrx == 0)
		printf(" S ");
	else if (room->place_mtrx == 1)
		printf(" E ");
	else
		printf("%3s", room->room);
	IF_FALSE((buf = str_is_int(s + i)));
	if ((room->x = ft_atoi(s + i)) < 0)
		return (-1);
	i += MOD(buf);
	IF_FALSE((buf = str_is_int(s + i)));
	if ((room->y = ft_atoi(s + i)) < 0)
		return (-1);
	i += MOD(buf);
	IF_FALSE(skip_spaces(s, &i));
	return ((int)(h % (NUM_ROOMS - 2)));
}

int			valid_room(char const *s, t_tbhash **th, size_t pow_p[],
		int f)
{
	t_tbhash	*room;
	int			res;

	CH_NULL(s);
	if (*s == 'L')
		return (1);
	room = init_room();
	if ((res = check_and_hash(room, s, pow_p)) == -1)
	{
		del_room(&room);
		return (1);
	}
	if (th[res] == NULL)
		th[res] = room;
	else if (collision(th, res, room) == 1)
	{
		del_room(&room);
		return (1);
	}
	if (f == 2)
		START = room;
	else if (f == 1)
		FINISH = room;
	return (0);
}
