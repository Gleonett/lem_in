/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:09:18 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/11 19:21:23 by gleonett         ###   ########.fr       */
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
			room->links[i]->p_x = room->p_x + 1;
			j = 0;
			while (room->links[i]->links[j] != room)
				j++;
			ft_swap((void **)room->links[i]->links,
					(void **)room->links[i]->links + j);
			queue(room->links[i], Q_ADD);
		}
	}
}

void			add_links_queue_2(t_tbhash *room, t_tbhash *start)
{
	short i;
	short j;

	if (room == start)
		return ;
	i = -1;
	while (++i < room->num_links)
	{
		if (room->links[i]->p_y == -1)
		{
			room->links[i]->p_y = room->p_y + 1;
			queue(room->links[i], Q_ADD);
		}
	}
}

t_tbhash		***init_bi_graph(int num_rooms)
{
	t_tbhash	***new;
	int			i;

	CH_NULL(new = (t_tbhash ***)malloc(sizeof(t_tbhash **) * (num_rooms + 1)));
	i = -1;
	while (++i < num_rooms)
		CH_NULL(new[i] = (t_tbhash **)malloc(sizeof(t_tbhash *) *
				(num_rooms + 1)));
	return (new);
}

void			sort_lvl(t_tbhash **bigraph, int num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && bigraph[j]->p_x < bigraph[j + 1]->p_x)
		{
			ft_swap((void **)(bigraph + j), (void **)(bigraph + j + 1));
			j--;
		}
	}
}

void			insert_bi_graph(t_tbhash ***bigrph, int num, t_tbhash *room)
{
	static short lvl;
	static short i;

	if (room == NULL)
	{
		while (++lvl < num)
			bigrph[lvl][0] = NULL;
		return ;
	}
	if (lvl != room->p_y)
	{
		bigrph[lvl][i] = NULL;
		sort_lvl(bigrph[lvl], i);
		lvl++;
		i = 0;
		bigrph[lvl + 1][0] = NULL;
	}
	bigrph[lvl][i] = room;
	bigrph[lvl][i + 1] = NULL;
	i++;
}

t_tbhash		***get_bigraph(t_tbhash ****srted_rooms, int n_r)
{
	t_tbhash	***b_g;
	int			i;
	int			j;
	int			k;

	CH_NULL(b_g = (t_tbhash ***)gc_memalloc(sizeof(t_tbhash **) *
			n_r + 1, "bg"));
	i = -1;
	k = -1;
	while (++i < n_r + 1)
	{
		j = -1;
		if ((*srted_rooms)[i][0] == NULL)
			break ;
		while (++j < n_r && (*srted_rooms)[i][j] != NULL)
		{
			if ((*srted_rooms)[i][j] != NULL)
			{
				printf("["PURPLE"%s"REBOOT"] ", (*srted_rooms)[i][j]->room);
				b_g[++k] = (*srted_rooms)[i][j]->links;
			}
		}
		ft_memdel((void **)((*srted_rooms) + i));
	}
	printf("\n");
	b_g[++k] = NULL;
	i--;
	while (++i < n_r)
		ft_memdel((void **)((*srted_rooms) + i));
	ft_memdel((void **)srted_rooms);
	return (b_g);
}

static t_tbhash **g_th;

void ft_recpritnt(t_tbhash *i)
{
	int j;

	j = (i == g_th[NUM_ROOMS - 2]) ? 0 : 1;
	ft_printf("%s --> ", i->room);
	if (i == g_th[NUM_ROOMS - 1])
		ft_printf("\n");
	else
	{
		i->flag = 1;
		while (j < i->num_links)
		{
			if (i->links[j]->flag != 1 && i->links[j]->num_links && i->p_x <=
			i->links[j]->p_x)
				ft_recpritnt(i->links[j]);
			j++;
		}
		i->flag = 0;
	}
}

int				bfs(t_tbhash **th, t_bigrph *b_g, int n_x_y[2], t_mtrx	mtrx)
{
	t_tbhash	*room;
	t_tbhash	***srted_rooms;

	START->p_x = 0;
	queue(START, Q_ADD);
	while((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue(room, FINISH);
		sort_links(th, room);
		n_x_y[0] = room->p_x;
	}
	srted_rooms = init_bi_graph(mtrx.num_a_r[1]);
	FINISH->p_y = 0;
	queue(FINISH, Q_ADD);
	while((room = queue(NULL, Q_GET)) != NULL)
	{
		add_links_queue_2(room, START);
		insert_bi_graph(srted_rooms, mtrx.num_a_r[1], room);
	}
	insert_bi_graph(srted_rooms, mtrx.num_a_r[1], NULL);
	print_bigraph(srted_rooms, mtrx.num_a_r);
	b_g->bi_graph = get_bigraph(&srted_rooms, mtrx.num_a_r[1]);
	print_bigraph(b_g->bi_graph, mtrx.num_a_r);
	g_th = th;
	ft_recpritnt(START);
	return (0);
}