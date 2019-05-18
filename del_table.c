/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:32:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/04 13:54:51 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_room(t_tbhash **room)
{
	ft_memdel((void **)&((*room)->room));
	ft_memdel((void **)&((*room)->links));
	ft_memdel((void **)room);
}

static void	del_room_list(t_tbhash **th, int j)
{
	t_tbhash *i;
	t_tbhash *back;

	i = th[j];
	while (i != NULL)
	{
		back = i;
		i = i->next;
		del_room(&back);
	}
}

void		del_tables(t_tbhash ***th)
{
	int i;

	i = -1;
	while (++i < NUM_ROOMS - 2)
	{
		if ((*th)[i] != NULL)
			del_room_list(*th, i);
	}
	(*th)[NUM_ROOMS - 2] = NULL;
	(*th)[NUM_ROOMS - 1] = NULL;
	ft_memdel((void **)th);
}

void		del_d_a_list(t_d_a **start)
{
	t_d_a	*i;
	t_d_a	*back;

	i = *start;
	while (i != NULL)
	{
		back = i;
		i = i->dist_ants;
		ft_memdel((void **)&back);
	}
}
