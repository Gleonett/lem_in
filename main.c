/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:41:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/12 14:33:41 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	error(t_tbhash **th)
{
	gc(NULL, GC_ALL, GC_DEL);
	del_tables(&th);
	ft_printf(RED"error"REBOOT": wrong input.\n");
	return (1);
}

int	main(void)
{
	t_tbhash	**th;
	t_mtrx		mtrx;
	t_th_pow_p	th_p;
	size_t		pow_p[SIZE_POW];

	mtrx.total_links = 0;
	CH_NULL(th = (t_tbhash **)ft_memalloc(sizeof(t_tbhash *) * NUM_ROOMS));
	power_p(pow_p);
	th_p.pow_p = pow_p;
	th_p.th = th;
	mtrx.num_a_r[1] = 0;
	mtrx.ways = NULL;
	if (reader(&th_p, &mtrx) == -1 || START == NULL || FINISH ==
	NULL || START->num_links == 0 || FINISH->num_links == 0)
		return (error(th));
	else if (mtrx.num_a_r[0] > 0)
		bfs(th);
	mtrx.total_links = mtrx.total_links - (short)mtrx.num_a_r[1];
	gc(NULL, GC_ALL, GC_DEL);
	prep_dfs(th, &mtrx, mtrx.num_a_r);
	prep_brute_force(th, &mtrx);
	distribution_ants(th, &mtrx);
}
