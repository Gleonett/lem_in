/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:49:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/11 18:23:57 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

short 		**init_mtrx(int num_rooms)
{
	short	**x;
	int		i;

	i = -1;
	CH_NULL(x = (short **)malloc(sizeof(short *) * num_rooms));
	while (++i < num_rooms)
		CH_NULL(x[i] = (short *)malloc(sizeof(short) * num_rooms));
	return (x);
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
	new->num_ant = 0;
	new->place_mtrx = place++;
	new->true_way = 0;
	new->p_x = -1;
	new->p_y = -1;
	new->flag = -1;
	new->num_links = 0;
	new->x = -1;
	new->y = -1;
	return (new);
}
