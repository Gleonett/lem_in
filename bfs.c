/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:09:18 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/24 18:38:21 by gleonett         ###   ########.fr       */
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
			room->links[i]->lvl  = 100 - room->links[i]->p_x;
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
		{
			room->links[i]->p_y = 22222;
		}
		else if (room->links[i]->p_y == -1)
		{
			room->links[i]->p_y = room->p_y + (short)1;
			room->links[i]->lvl += room->links[i]->p_y * 1000;
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
			queue(room->links[i], Q_ADD);
		}
	}
}

int				bfs(t_tbhash **th, int n_x_y[2], t_mtrx	mtrx)
{
	t_tbhash	*room;
//	t_tbhash	***srted_rooms;


	START->p_x = 0;
	queue(START, Q_ADD);
	while((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue(room, FINISH);
		//		n_x_y[0] = room->p_x;
	}
	FINISH->p_y = 0;
	queue(FINISH, Q_ADD);
	while((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue_2(room, START);
		//		insert_bi_graph(srted_rooms, mtrx.num_a_r[1], room);
	}
//	srted_rooms = init_bi_graph(mtrx.num_a_r[1]);

	START->p_z = 1;
	queue(START, Q_ADD);
	while((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue_3(room, FINISH);
		sort_links(th, room);
		if (room->deleted != 1)
		{
			ft_printf("\n%s y = %d  lvl = %d ", room->room, room->p_y, room->lvl);
			int k = -1;
			while (++k < room->num_links)
				if (room->links[k] == NULL)
					ft_printf("%s", NULL);
				else
					ft_printf("%s ", room->links[k]->room);
		}
		//		insert_bi_graph(srted_rooms, mtrx.num_a_r[1], room);
	}

//	insert_bi_graph(srted_rooms, mtrx.num_a_r[1], NULL);
//	b_g->bi_graph = get_bigraph(&srted_rooms, mtrx.num_a_r[1]);
	//	print_bigraph(srted_rooms, mtrx.num_a_r);
	//	print_bigraph(b_g->bi_graph, mtrx.num_a_r);
	return (0);
}