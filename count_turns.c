/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_turns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:50:12 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/19 20:03:15 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			count_turns(short **final_ways, t_mtrx *ways, short *k)
{
	int buf;
	int *dstrbtd_ants;

	if (final_ways == NULL || *final_ways == NULL)
		return (MAX_INT);
	*k = 0;
	while (final_ways[*k] != NULL)
		*k += 1;
	if ((dstrbtd_ants = find_num_ants(ways->num_a_r[0], final_ways, *k,
			ways->num_a_r[1])) == NULL)
		return (MAX_INT);
	buf = dstrbtd_ants[0] + final_ways[0][ways->num_a_r[1]];
	ft_memdel((void **)&dstrbtd_ants);
	return (buf);
}
