/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_num_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:49:24 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/14 17:49:26 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*find_num_ants(int ants, short **final_ways, short num_ways, int j)
{
	int *dstrbtd_ants;
	int i;
	int k;

	if (num_ways == 0)
		return (NULL);
	CH_NULL(dstrbtd_ants = (int *)ft_memalloc(sizeof(int) * num_ways));
	i = 1;
	k = 1;
	dstrbtd_ants[0] += 1;
	while (i < ants)
	{
		if (k == num_ways || final_ways[k][j] + dstrbtd_ants[k] >
				final_ways[0][j] + dstrbtd_ants[0] - 1)
		{
			dstrbtd_ants[0] += 1;
			i++;
			k = 1;
			continue ;
		}
		dstrbtd_ants[k] += 1;
		i++;
		k++;
	}
	return (dstrbtd_ants);
}
