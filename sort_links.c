/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:28:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/30 17:02:24 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

void	final_room(t_tbhash **links, int num_links)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < num_links)
	{
		if (links[i]->true_way == 1)
		{
			if (links[j] == NULL)
			{
				links[j] = links[i];
				links[i] = NULL;
			}
			else
				while (j < i && links[j] != NULL)
					j++;
		}
		else
			links[i] = NULL;
	}
}

void	start_room(t_tbhash *room)
{
	int i;
	int j;
	int num;
	t_tbhash *lol;

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
}

void	sort_links(t_tbhash **th, t_tbhash *room, t_tbhash *start)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (room == start)
		start_room(room);
//	else if ()
}