/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_metods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:54:03 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/05 13:54:10 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

short	find_min(t_tbhash *room, t_tbhash *next_room)
{
	short short_way;
	short j;
	short i;

	short_way = next_room->p_x;
	i = 0;
	while (++i < room->num_links)
	{
		if (short_way >= next_room->p_x)
			if (ft_strcmp(room->room, next_room->room) != 0)
				room->links[j]->p_x > room->links[i]->p_x ? j = i : 0;
	}
	return (-1);
}