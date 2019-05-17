/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:28:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/28 15:26:40 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		smallest_connectivity(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j]->p_x == links[j + 1]->p_x)
		{
			if (links[j]->p_y > links[j + 1]->p_y)
				ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

static void		sort_lvl(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j + 1] != NULL && (links[j] == NULL ||
				links[j]->p_x < links[j + 1]->p_x))
		{
			ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

static size_t	start_room(t_tbhash **links, short num)
{
	size_t	num_dead_ends;
	int		i;

	i = -1;
	num_dead_ends = 0;
	while (++i < num && links[i]->p_y < 0)
		num_dead_ends++;
	ft_memmove(links, links + num_dead_ends, sizeof(short *) * (num -
	num_dead_ends));
	ft_bzero(links + num - num_dead_ends, sizeof(short *) * (num_dead_ends));
	return (num_dead_ends);
}

static void		finish_room(t_tbhash **links, short num)
{
	int i;
	int j;

	i = -1;
	while (++i < num)
	{
		if (ft_strcmp("14", links[i]->room) == 0)
			ft_printf("");
		j = -1;
		while (++j < links[i]->num_links)
			if (links[i]->links[j]->p_x == MAX_SHORT)
			{
				if (j == 0)
					continue ;
				links[i]->links[0] = links[i]->links[j];
				links[i]->links[j] = NULL;
			}
			else
				links[i]->links[j] = NULL;
		links[i]->num_links = 1;
	}
}

void			sort_links(t_tbhash **th, t_tbhash *room)
{
	sort_lvl(room->links, room->num_links);
	if (room == START)
		room->num_links -= start_room(room->links, room->num_links);
	if (room == FINISH)
	{
		finish_room(room->links, room->num_links);
	}
	smallest_connectivity(room->links, room->num_links);
}
