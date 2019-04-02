/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:49:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/02 11:04:15 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tbhash	****init_field(int n_r, int n_x_y[])
{
	const int	n_z = n_r - n_x_y[0] - n_x_y[1];
	t_tbhash	****field;
	int			i;
	int			j;

	CH_NULL(field = (t_tbhash ****)malloc(sizeof(t_tbhash ***) * n_x_y[0]));
	i = -1;
	while (++i < n_x_y[0])
	{
		CH_NULL(field[i] = (t_tbhash ***)malloc(sizeof(t_tbhash **) *
				(n_x_y[1])));
		j = -1;
		while (++j < n_x_y[1])
		{
			CH_NULL(field[i][j] = (t_tbhash **)malloc(sizeof(t_tbhash *) *
					n_z));
			field[i][j][0] = NULL;
		}
	}
	return (field);
}

t_tbhash	*init_room(void)
{
	t_tbhash		*new;
	static short	place;

	CH_NULL(new = (t_tbhash *)malloc(sizeof(t_tbhash)));
	CH_NULL(new->links = (t_tbhash **)malloc(sizeof(t_tbhash *) *
			NUM_LINKS));
	new->links[0] = NULL;
	new->queue_prev = NULL;
	new->room = NULL;
	new->next = NULL;
	new->way = NULL;
	new->place_mtrx = place++;
	new->true_way = 0;
	new->p_x = -1;
	new->p_y = -1;
	new->p_z = -1;
	new->num_links = 0;
	new->x = -1;
	new->y = -1;
	return (new);
}
