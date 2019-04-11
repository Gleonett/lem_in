/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:38:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/05 18:48:26 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ways	**max_ways(t_tbhash *start)
{
	t_ways		**ways;
	short i;

	ways = (t_ways **)malloc(sizeof(t_ways *) * (start->num_links + 1));
	ways[start->num_links] = NULL;
	i = -1;
	while(++i < start->num_links)
	{
		ways[i] = (t_ways *)malloc(sizeof(t_ways));
		ways[i]->room = start->links[i];
	}
	return (ways);
}

//	stream(field, mtrx, moves);

int			prep_stream(t_tbhash *start, t_tbhash *finish, t_mtrx mtrx)
{
	t_ways		**ways;
	int 		min_ways;

//	ways = max_ways(start);
//	ft_memdel((void **)&ways);
	return (0);
}
