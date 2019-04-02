/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:41:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/02 11:28:08 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_tbhash	**th;
	t_tbhash	****field;
	t_mtrx		mtrx;
	size_t		pow_p[SIZE_POW];
	int			n_x_y[2];

	CH_NULL(th = (t_tbhash **)malloc(sizeof(t_tbhash *) * NUM_ROOMS));
	power_p(pow_p);
	mtrx.num_a_r[1] = 0;
	if (reader(th, pow_p, &mtrx) == -1 || START == NULL || FINISH ==
	NULL)
	{
		gc(NULL, GC_ALL, GC_DEL);
		del_tables(&th, NULL, mtrx.num_a_r[1], 0);
		ft_printf(RED"error"REBOOT": wrong input.\n");
		return (1);
	}
	else if (mtrx.num_a_r[0] > 0)
	{
		bfs(th, &field, n_x_y, mtrx);
	}
	gc(NULL, GC_ALL, GC_DEL);
	del_tables(&th, &field, mtrx.num_a_r[1], n_x_y);
	return (0);
}
