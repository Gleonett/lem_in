/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:09:18 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/26 17:44:35 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static t_tbhash	*queue(t_tbhash *new_room, char add_get)
{
	static	t_tbhash	*end;
	static	t_tbhash	*front;
	t_tbhash			*ret;

	if (add_get == Q_ADD && new_room != NULL)
	{
		front == NULL ? front = new_room : 0;
		end != NULL ? end->queue_prev = new_room : 0;
		end = new_room;
		return (NULL);
	}
	else if (add_get == Q_GET && front != NULL)
	{
		ret = front;
		front = front->queue_prev;
		front == NULL ? end = NULL : 0;
		ret->queue_prev = NULL;
		return (ret);
	}
	return (NULL);
}

void			add_links_queue(t_tbhash *room, t_tbhash *finish)
{
	short i;
	short j;

	if (room == finish)
		return ;
	i = -1;
	while (++i < room->num_links)
	{
		if (room->links[i]->p_x == -1)
		{
			room->links[i]->p_x = room->p_x + (short)1;
			room->links[i]->lvl = 100 - room->links[i]->p_x;
			queue(room->links[i], Q_ADD);
		}
	}
}

void			add_links_queue_2(t_tbhash *room, t_tbhash *start)
{
	short i;

	if (room == start)
		return ;
	i = -1;
	while (++i < room->num_links)
	{
		if (room->links[i] == start)
			room->links[i]->p_y = 32767;
		else if (room->links[i]->p_y == -1)
		{
			room->links[i]->p_y = room->p_y + (short)1;
			queue(room->links[i], Q_ADD);
		}
	}
}

void			add_links_queue_3(t_tbhash *room, t_tbhash *start)
{
	short i;

	if (room == start)
		return ;
	i = -1;
	while (++i < room->num_links)
	{
		if (room->links[i] != NULL && room->links[i]->p_z == -1)
		{
			room->links[i]->p_z = 1;
			room->links[i]->lvl += room->links[i]->p_y * 1000;
			queue(room->links[i], Q_ADD);
		}
	}
}

int				bfs(t_tbhash **th)
{
	t_tbhash	*room;

	START->p_x = 0;
	queue(START, Q_ADD);
	while ((room = queue(NULL, Q_GET)) != NULL)
		add_links_queue(room, FINISH);
	FINISH->p_x = MAX_SHORT;
	FINISH->p_y = 0;
	queue(FINISH, Q_ADD);
	while ((room = queue(NULL, Q_GET)) != NULL)
		add_links_queue_2(room, START);
	START->lvl = 2147483647;
	START->p_z = 1;
	queue(START, Q_ADD);
	while ((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue_3(room, FINISH);
		room == FINISH ? 0 : sort_links(th, room);
	}
	sort_links(th, START);
	sort_links(th, FINISH);
	ft_printf("\n");
	return (0);
}
