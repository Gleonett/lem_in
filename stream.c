/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:31:21 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/04 19:29:02 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	iter(int xyz[], short flag)
{
	if (flag == XP_YM)
	{
		xyz[0] += 1;
		xyz[1] -= 1;
	}
	else if (flag == Z_PL)
		xyz[2] += 1;
	else if (flag == X_PL)
		xyz[0] += 1;
	else if (flag == Y_MI)
		xyz[1] -= 1;
	else if (flag == Y_PL)
		xyz[1] += 1;
	else if (flag == X_MI)
		xyz[0] -= 1;
	else if (flag == XM_YP)
	{
		xyz[0] -= 1;
		xyz[1] += 1;
	}
	if (flag != 2)
		xyz[2] = 0;
}

short find_start_ways(t_tbhash ****field, t_tbhash *start, int num_ants,
		t_tbhash **moves)
{
	int xyz[3];
	int i;

	ft_bzero(xyz, (sizeof(int) * 3));
	xyz[1] = start->p_y;
	iter(xyz, XP_YM);
	i = start->num_links > num_ants ? num_ants : start->num_links;
	moves[i - 1] = field[xyz[0]][xyz[1]][xyz[2]];
	iter(xyz, Z_PL);
	i--;
	while (field[xyz[0]][xyz[1]][xyz[2]]-> != NULL || i > 0)
	{
		moves[--i] = field[xyz[0]][xyz[1]][xyz[2]];
		iter(xyz, Z_PL);
	}
	i--;
	while (i > 0)
	{
		iter(xyz, Y_PL);
		if ((moves[i] = field[xyz[0]][xyz[1]][xyz[2]]) != NULL)
		{
			i--;
			iter(xyz, Z_PL);
			while ((moves[i] = field[xyz[0]][xyz[1]][xyz[2]]) != NULL && i > 0)
			{
				i--;
				iter(xyz, Z_PL);
			}
		}
	}
	return ((short)(start->num_links > num_ants ? num_ants : start->num_links));
}

void			stream(t_tbhash ****field, t_mtrx mtrx, t_tbhash **moves)
{
	short num_streams;

	num_streams = find_start_ways(field, mtrx.start, mtrx.num_a_r[0], moves);
//	while (mtrx.num_a_r[0] > 0)
//	{
//		find_field
//	}
}