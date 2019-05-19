/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:49:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/24 16:27:47 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tbhash		*init_room(void)
{
	t_tbhash		*new;
	static short	place;

	CH_NULL(new = (t_tbhash *)malloc(sizeof(t_tbhash)));
	CH_NULL(new->links = (t_tbhash **)malloc(sizeof(t_tbhash *) * NUM_LINKS));
	new->links[0] = NULL;
	new->queue_prev = NULL;
	new->room = NULL;
	new->next = NULL;
	new->place_mtrx = place++;
	new->p_x = -1;
	new->p_y = -1;
	new->p_z = -1;
	new->flag = -1;
	new->num_links = 0;
	new->lvl = 0;
	return (new);
}

void			add_start_d_a(t_d_a **start_list, short num)
{
	t_d_a			*new;
	static short	i;

	if (num == 0)
	{
		if (i > 0)
			return ;
		i++;
	}
	CH_NULL(new = (t_d_a *)malloc(sizeof(t_d_a)));
	new->num_ants_in_turn = num;
	if (*start_list == NULL)
		new->dist_ants = NULL;
	else
		new->dist_ants = *start_list;
	*start_list = new;
}
