/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lvls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:37:54 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/09 12:37:57 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void sort_ways(short **links, int len, short index)
{
	short i;
	short j;

	if (len == 0)
		return ;
	i = -1;
	while (++i + 1 < len)
	{
		j = i;
		while (j > -1 && links[j][index] > links[j + 1][index])
		{
			ft_swap((void **)links + j, (void **)links + j + 1);
			j--;
		}
	}
}

void sort_lvls_in_mtrx(short *num_lvls, short **ways, t_mtrx *mtrx)
{
	int z;
	int k;

	z = 1;
	while (num_lvls[z] != -1)
	{
		k = z - 1;
		while (k > 0 && num_lvls[k] == 0)
			k--;
		sort_ways(ways + num_lvls[k], num_lvls[z] - num_lvls[k], (short)
		(mtrx->num_a_r[1]));
		z++;
	}
	print_mtrx(ways, mtrx->num_a_r[1]);
}
