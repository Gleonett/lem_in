/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:41:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/04 18:45:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_mtrx(t_mtrx mtrx)
{
	int i;
	int j;

	i = -1;
	printf("\n");
	while (++i < mtrx.num_a_r[1])
	{
		j = -1;
		while (++j < mtrx.num_a_r[1])
		{
			if (mtrx.mtrx[i][j] == 0)
				printf("["PURPLE"%d"REBOOT"]", mtrx.mtrx[i][j]);
			else
				printf("["YELLOW"%d"REBOOT"]", mtrx.mtrx[i][j]);
		}
		printf("\n");
	}
}


void	print_field(t_tbhash ****field, int num_rooms, int num_x, int num_y)
{
	int x;
	int y;
	int z;

	y = num_y;
	while (--y > -1)
	{
		x = -1;
		while (++x < num_x)
		{
			printf("[");
			z = -1;
			while (field[x][y][++z] != NULL)
				if (z == 0)
					printf(GREEN"%*s"REBOOT, field[x][y][z + 1] == NULL ? 6 : 3,
						   field[x][y][z] == NULL ? NULL : field[x][y][z]->room);
				else
					printf(PURPLE"%3s"REBOOT, field[x][y][z]->room);
			if (z == 0 && field[x][y][z] == NULL)
				printf("%6s", "");
			printf("]");
		}
		printf("\n");
	}
}


int	main(void)
{
	t_tbhash	**th;
	t_tbhash	****field;
	t_mtrx		mtrx;
	size_t		pow_p[SIZE_POW];
	int			n_x_y[2];

	CH_NULL(th = (t_tbhash **)ft_memalloc(sizeof(t_tbhash *) * NUM_ROOMS));
	power_p(pow_p);
	mtrx.num_a_r[1] = 0;
	mtrx.mtrx = NULL;
	if (reader(th, pow_p, &mtrx) == -1 || START == NULL || FINISH ==
	NULL || START->num_links == 0 || FINISH->num_links == 0)
	{
		gc(NULL, GC_ALL, GC_DEL);
		del_tables(&th, NULL, mtrx.num_a_r[1], 0);
		del_mtrx(&mtrx);
		ft_printf(RED"error"REBOOT": wrong input.\n");
		return (1);
	}
	else if (mtrx.num_a_r[0] > 0)
	{
		bfs(th, &field, n_x_y, mtrx);
	}
//	bruteforce(x, y, z);
	gc(NULL, GC_ALL, GC_DEL);
	print_field(field, mtrx.num_a_r[1], n_x_y[0], n_x_y[1]);
	mtrx.start = START;
	mtrx.finish = FINISH;
	prep_stream(field, START, FINISH, mtrx);
	//	print_mtrx(mtrx);
	del_tables(&th, &field, mtrx.num_a_r[1], n_x_y);
	del_mtrx(&mtrx);
	return (0);
}
