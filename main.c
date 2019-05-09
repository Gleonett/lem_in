/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:41:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/09 17:56:10 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_mtrx(short **mtrx, int num)
{
	int i;
	int j;

	i = -1;
	printf("\n");
	while (++i < num && mtrx[i][num - 1] != 0)
	{
		j = -1;
		while (++j < num)
		{
			if (mtrx[i][j] == 0)
				printf("");
//				printf("["PURPLE"%5d"REBOOT"]", mtrx[i][j]);
			else
				printf("["YELLOW"%5d"REBOOT"]", mtrx[i][j]);
		}
		printf("\n");
	}
}

int	main(void)
{
	t_tbhash	**th;
	t_mtrx		mtrx;
	size_t		pow_p[SIZE_POW];
	int			n_x_y[2];
	short 		**ways;

	mtrx.total_links = 0;
	CH_NULL(th = (t_tbhash **)ft_memalloc(sizeof(t_tbhash *) * NUM_ROOMS));
	power_p(pow_p);
	mtrx.num_a_r[1] = 0;
	mtrx.ways = NULL;
	if (reader(th, pow_p, &mtrx) == -1 || START == NULL || FINISH ==
	NULL || START->num_links == 0 || FINISH->num_links == 0)
	{
		gc(NULL, GC_ALL, GC_DEL);
		del_tables(&th);
//		del_mtrx(&mtrx);
		ft_printf(RED"error"REBOOT": wrong input.\n");
		return (1);
	}
	else if (mtrx.num_a_r[0] > 0)
		bfs(th, n_x_y, mtrx);
	mtrx.total_links = mtrx.total_links - (short)mtrx.num_a_r[1];
	ft_printf("\n%d - rooms\n%d - links\n"RED"\nDIFFERENT = %d\n"REBOOT,
			  mtrx.num_a_r[1], mtrx.total_links,
			  mtrx.total_links - mtrx.num_a_r[1]);
	gc(NULL, GC_ALL, GC_DEL);
	prep_dfs(th, &mtrx, mtrx.num_a_r);
	prep_brute_force(th, &mtrx);
	distribution_ants(th, &mtrx);
//	print_mtrx(mtrx);
//	del_tables(&th, mtrx.num_a_r[1], n_x_y);
//	del_mtrx(&mtrx);
	return (0);
}
