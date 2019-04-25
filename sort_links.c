/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:28:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/25 13:25:41 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

void	smallest_connectivity(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j]->p_y == links[j + 1]->p_y)
		{
			if (links[j]->num_links > links[j + 1]->num_links &&
					links[j]->p_x != 0)
				ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

void	sort_lvl(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j + 1] != NULL && (links[j] == NULL ||
				links[j]->lvl > links[j + 1]->lvl))
		{
			ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

size_t start_room(t_tbhash **links, short num)
{
	int i;
	size_t num_dead_ends;

	i = -1;
	num_dead_ends = 0;
	while (++i < num && links[i]->lvl < 0)
		num_dead_ends++;
	ft_memmove(links, links + num_dead_ends, sizeof(short *) * (num -
	num_dead_ends));
	ft_bzero(links + num - num_dead_ends, sizeof(short *) * (num_dead_ends));
	return (num_dead_ends);
}

void finish_room(t_tbhash **links, short num)
{
	int i;
	int j;

	i = -1;
	while (++i < num)
	{
		j = 0;
		while (++j < links[i]->num_links)
			links[i]->links[j] = NULL;
		links[i]->num_links = 1;
	}
}


void	sort_links(t_tbhash **th, t_tbhash *room)
{
	sort_lvl(room->links, room->num_links);
	if (room == START)
		room->num_links -= start_room(room->links, room->num_links);
	if (room == FINISH)
		finish_room(room->links, room->num_links);
	else
		smallest_connectivity(room->links, room->num_links);
}