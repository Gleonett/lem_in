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

void		del_room_list(t_tbhash **th, int j)
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

void		del_field(t_tbhash *****field, int n_r, int n_x_y[])
{
	int i;
	int j;

	i = n_x_y[0];
	while (--i > -1)
	{
		j = n_x_y[1];
		while (--j > -1)
			ft_memdel((void *)&(field[0][i][j]));
		ft_memdel((void **)&(field[0][i]));
	}
	ft_memdel((void **)field);
}

void		del_tables(t_tbhash ***th, t_tbhash *****field, int n_r, int n_xy[])
{
	int i;

	i = -1;
	while (++i < NUM_ROOMS - 2)
		if ((*th)[i] != NULL)
			del_room_list(*th, i);
	(*th)[NUM_ROOMS - 2] = NULL;
	(*th)[NUM_ROOMS - 1] = NULL;
	ft_memdel((void **)th);
	if (field != NULL)
		del_field(field, n_r, n_xy);
}


void		del_mtrx(t_mtrx *mtrx)
{
	int i;

	i = -1;
	while (++i < mtrx->num_a_r[1])
		ft_memdel((void **)mtrx->mtrx + i);
	ft_memdel((void**)&(mtrx->mtrx));
}