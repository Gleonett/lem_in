/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:28:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/24 18:24:27 by gleonett         ###   ########.fr       */
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

void	sort_y(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j + 1] != NULL && (links[j] == NULL ||
			links[j]->p_y > links[j + 1]->p_y))
		{
			ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

void	sort_x(t_tbhash **links, short num)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j + 1] != NULL && (links[j] == NULL ||
		links[j]->p_y == links[j + 1]->p_y))
		{
			if (links[j]->p_x > links[j + 1]->p_x &&
					links[j]->p_x != 0)
			{
				ft_swap((void **) links + j, (void **) links + j + 1);
				i = j - 1;
			}
			j--;
		}
	}
}

//void	makelvl(t_tbhash **links, short num)
//{
//	short i;
//
//	i = -1;
//	while (++i < num)
//		links[i]->lvl += links[i]->p_x;
//}

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
	sort_y(room->links, room->num_links);
	smallest_connectivity(room->links, room->num_links);
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

void	del_links_left(t_tbhash *start, t_tbhash *room)
{
	int i;
	int j;
	int num;
	int flag;

	if (room == NULL)
		return ;
	i = -1;
	j = 0;
	num = 0;
	flag = 0;
	while (++i < room->num_links)
	{
		if (room->links[i] == NULL)
			continue ;
		while (j < i && room->links[j] != NULL)
			j++;
		if (room->links[i] == start || room->links[i]->p_y == 0 ||
		(room->links[i]->lvl > room->lvl && room->links[i]->deleted != 1))
			flag++;
		if (room->p_y != 0 && (room->links[i]->deleted == 1 ||
		(room->links[i]->lvl > room->lvl)))
			room->links[i] = NULL;
		if (room->links[j] == NULL)
			ft_swap((void **)room->links + j, (void **)room->links + i);
	}
	room->num_links -=num;
	flag == 0 ? ft_printf("\n%s", room->room), room->deleted = 1 : 0;
}

void rec_del_links(t_tbhash *start, t_tbhash *room)
{
	int i;
	int k;
	i = -1;

	if (room != NULL && room->deleted == 1)
	{
		while (++i < room->num_links)
		{
			if (room->links[i] != NULL && room->links[i] != start &&
					room->links[i]->deleted != 1)
				del_links_left(start, room->links[i]);
			rec_del_links(start, room->links[i]);
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

void	sort_links(t_tbhash **th, t_tbhash *room)
{
	if (room == START)
		start_room(room);
	else if (room == FINISH)
		finish_room(room);
	else
		sort_lvl(room->links, room->num_links);
//	else if (room->p_x >= START->p_x)
//	{
//		del_links_right(FINISH, room);
//		sort(room->links, room->num_links);
//		smallest_connectivity(room->links, room->num_links);
//	}
//	else
//	{
//		sort_x(room->links, room->num_links);
		//makelvl(room->links, room->num_links);
//		if (room != START)
//			del_links_left(START, room);
//		rec_del_links(START, room);
	//		smallest_connectivity(room->links, room->num_links);
//	}
}