/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:09:18 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/02 11:04:15 by gleonett         ###   ########.fr       */
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
	int i;

	i = -1;
	if (room == finish)
		return ;
	while (++i < room->num_links)
	{
		if (room->links[i]->p_x  == -1)
		{
			room->links[i]->p_x = room->p_x + 1;
			queue(room->links[i], Q_ADD);
		}
	}
}

void			add_links_queue_2(t_tbhash *room, t_tbhash *finish)
{
	int i;

	i = -1;
	if (room == finish)
		return ;
	while (++i < room->num_links)
	{
		if (room->links[i]->p_y  == -1)
		{
			room->links[i]->p_y = room->p_y + 1;
			queue(room->links[i], Q_ADD);
		}
	}
}


void	print_field(t_tbhash ****field, int num_rooms, int num_x, int num_y)
{
	int x;
	int y;
	int z;
	int flag;

	flag = 0;
	y = num_y;
	while (--y > -1)
	{
//		while (flag != 1 && field[0][y][0] == NULL)
//			y--;
//		flag = 1;
		x = -1;
		while (++x < num_x)
		{
			printf("[");
			z = -1;
			while (field[x][y][++z] != NULL)
				if (z == 0)
					printf(GREEN"%*s"REBOOT, field[x][y][z + 1] == NULL ? 6 : 3,
						field[x][y][z] == NULL ? NULL : field[x][y][z]->room);
				else
					printf(PURPLE"%3s"REBOOT, field[x][y][z]->room);
			if (z == 0 && field[x][y][z] == NULL)
				printf("%6s", "");
			printf("]");
		}
		printf("\n");
	}
}

void	insert_in_field(t_tbhash ****field, t_tbhash *room)
{
	int			z;
	t_tbhash	*buf;

	if (room->p_x < 0 || room->p_y < 0)
		return ;
	buf = room;
	z = -1;
	while (field[room->p_x][room->p_y][++z] != NULL)
	{
		if (field[room->p_x][room->p_y][z]->num_links > room->num_links)
			ft_swap((void **)(field[room->p_x][room->p_y] + z), (void **)&buf);
	}
	field[room->p_x][room->p_y][z] = buf;
	field[room->p_x][room->p_y][z + 1] = NULL;
}

void			add_links_queue_3(t_tbhash *room)
{
	int i;

	i = -1;
	while (++i < room->num_links)
	{
		if (room->links[i]->p_z  == -1)
		{
			room->links[i]->p_z = room->p_z + 1;
			queue(room->links[i], Q_ADD);
		}
	}
}

int				bfs(t_tbhash **th, t_tbhash *****field, int n_x_y[2],
		t_mtrx	mtrx)
{
	t_tbhash *start;
	t_tbhash *finish;
	t_tbhash *room;

	start = START->num_links <= FINISH->num_links ? START : FINISH;
	finish = start == START ? FINISH : START;
	start->p_x = 0;
	queue(start, Q_ADD);
	while((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue(room, finish);
		n_x_y[0] = room->p_x;
	}
	finish->p_y = 0;
	queue(finish, Q_ADD);
	while ((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue_2(room, start);
		n_x_y[1] = room->p_y;
	}
	n_x_y[0] += 1;
	n_x_y[1] += 1;
	*field = init_field(mtrx.num_a_r[1], n_x_y);
	START->p_z = 0;
	queue(START, Q_ADD);
	while ((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue_3(room);
		insert_in_field(*field, room);
	}
	print_field(*field, mtrx.num_a_r[1], n_x_y[0], n_x_y[1]);
	return (0);
}
