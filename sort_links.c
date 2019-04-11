/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:28:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/05 16:47:32 by gleonett         ###   ########.fr       */
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
		while (j > -1 && links[j]->p_x == links[j + 1]->p_x)
		{
			if (links[j]->num_links > links[j + 1]->num_links)
				ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

void	sort(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j]->p_x > links[j + 1]->p_x)
		{
			ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

void	start_room(t_tbhash *room)
{
	int i;
	int j;
	int num;

	i = -1;
	j = 0;
	num = 0;
	while (++i < room->num_links)
	{
		if (room->links[i]->p_x == -1)
		{
			room->links[i] = NULL;
			num++;
		}
		while (j < i && room->links[j] != NULL)
			j++;
		if (room->links[i] != NULL)
			if (room->links[j] == NULL)
			{
				room->links[j] = room->links[i];
				room->links[i] = NULL;
			}
	}
	room->num_links -= num;
	sort(room->links, room->num_links);
	smallest_connectivity(room->links, room->num_links);
}

void	sort_links(t_tbhash **th, t_tbhash *room)
{
	if (room == START)
		start_room(room);
	else
	{
		sort(room->links, room->num_links);
		smallest_connectivity(room->links, room->num_links);
	}
}