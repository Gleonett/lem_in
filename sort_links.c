/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:28:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/14 11:53:33 by gleonett         ###   ########.fr       */
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

void	sort(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j]->p_y > links[j + 1]->p_y)
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
		if (room->links[i]->p_y == -1)
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

void	del_links(t_tbhash *finish, t_tbhash *room)
{
	int i;
	int j;
	int num;

	i = -1;
	j = 0;
	num = 0;
	while (++i < room->num_links)
	{
		while (j < i && room->links[j] != NULL)
			j++;
		if (((room->p_x > room->links[i]->p_x && room->p_y >room->links[i]->p_y)
		|| (room->p_x == room->links[i]->p_x && room->p_y < room->links[i]->p_y)
		|| (room->p_x > room->links[i]->p_x && room->p_y <= room->links[i]->p_y)
		) && room->links[i] != finish)
		{
			room->links[i] = NULL;
			num++;
		}
		if (room->links[j] == NULL)
			ft_swap((void **)room->links + j, (void **)room->links + i);
	}
	room->num_links -=num;
}

void	finish_room(t_tbhash *finish)
{
	int i;
	int j;
	t_tbhash *room;

	i = -1;
	while (++i < finish->num_links)
	{
		room = finish->links[i];
		if (room->p_x == 0)
			continue ;
		j = -1;
		while (++j < room->num_links)
		{
			if (room->links[j] == finish)
				ft_swap((void **)room->links + j, (void **)room->links);
			else
				room->links[j] = NULL;
		}
		room->num_links = 1;
	}
}

void	sort_links(t_tbhash **th, t_tbhash *room)
{
	if (room == START)
		start_room(room);
	else if (room == FINISH)
	{
		finish_room(room);
	}
	else
	{
		del_links(FINISH, room);
		sort(room->links, room->num_links);
		smallest_connectivity(room->links, room->num_links);
	}
}