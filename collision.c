/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:04:17 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/20 15:04:10 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	collision(t_tbhash **th, int res, t_tbhash *room)
{
	t_tbhash *i;

	i = th[res];
	while (i != NULL)
	{
		if (ft_strcmp(i->room, room->room) == 0)
			return (1);
		i = i->next;
	}
	room->next = th[res];
	th[res] = room;
	return (0);
}
