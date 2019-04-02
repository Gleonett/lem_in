/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:44:05 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/24 16:33:07 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	hash_room(size_t pow_p[], const char *s, int *i)
{
	size_t	h;
	int		j;

	h = 0;
	j = -1;
	while (s[*i] > ' ' && s[*i] < 127 && s[*i] != '-' && s[*i])
	{
		if (++j < SIZE_POW)
			h += (s[*i] * pow_p[j]);
		else
			h += (s[*i] * power_p_more(pow_p[SIZE_POW - 1], (size_t)j));
		*i += 1;
	}
	return ((int)(h % (NUM_ROOMS - 2)));
}

t_tbhash	*find_room(t_tbhash **th, int h, const char *s)
{
	t_tbhash *i;

	i = th[h];
	while (i != NULL)
	{
		if (ft_strstr(s, i->room) == s)
			return (i);
		i = i->next;
	}
	return (NULL);
}

static void	add_size(t_tbhash **room)
{
	t_tbhash **arr;

	arr = (t_tbhash **)malloc(sizeof(t_tbhash *) * ((*room)->num_links
			+ NUM_LINKS));
	ft_memcpy(arr, (*room)->links, sizeof(t_tbhash *) * ((*room)->num_links));
	ft_memdel((void **)&((*room)->links));
	(*room)->links = arr;
}

static void	init_links(t_tbhash **room1, t_tbhash **room2)
{
	int i;

	i = -1;
	while ((*room1)->links[++i] != NULL)
	{
		if ((*room1)->links[i] == *room2)
			return ;
	}
	(*room1)->num_links += 1;
	(*room2)->num_links += 1;
	if ((*room1)->num_links >= NUM_LINKS - 1)
		add_size(room1);
	if ((*room2)->num_links >= NUM_LINKS - 1)
		add_size(room2);
	(*room1)->links[(*room1)->num_links - 1] = *room2;
	(*room2)->links[(*room2)->num_links - 1] = *room1;
	(*room1)->links[(*room1)->num_links] = NULL;
	(*room2)->links[(*room2)->num_links] = NULL;
}

int			valid_links(t_tbhash **th, size_t pow_p[], const char *s)
{
	int			ij[2];
	int			h1;
	int			h2;
	t_tbhash	*room1;
	t_tbhash	*room2;

	ij[0] = 0;
	h1 = hash_room(pow_p, s, ij);
	if ((room1 = find_room(th, h1, s)) == NULL)
		return (1);
	if (s[ij[0]] != '-')
		return (-1);
	ij[0] += 1;
	ij[1] = ij[0];
	h2 = hash_room(pow_p, s, ij);
	if ((room2 = find_room(th, h2, s + ij[1])) == NULL)
		return (1);
	init_links(&room1, &room2);
	return (0);
}
