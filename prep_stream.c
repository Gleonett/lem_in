/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:38:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/12 15:55:28 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_for_dfs	g_ways;

static int	del_way(int way, short ret_fill, short **ways, int len)
{
	int k;

	k = way + 1;
	while (--k > -1 && k >= ret_fill)
		ways[k][len] = 0;
	return (-1);
}

static int	insert_room(t_for_dfs *ways, int ret_fill, int lvl, t_tbhash *i)
{
	int k;

	k = (short)ways->way;
	while (--k > -1 && k > ret_fill &&
	ways->ways[k][ways->num_rooms - 1] == lvl)
		ways->ways[k][i->place_mtrx] = lvl;
	return (-4);
}

static int	final_room(t_for_dfs *ways, int lvl, t_tbhash *i, int len)
{
	ways->ways[ways->way][i->place_mtrx] = 0;
	ways->ways[ways->way][ways->num_rooms - 1] = lvl;
	ways->ways[ways->way][ways->num_rooms] = len;
	ways->way += 1;
	return (-2);
}

short		dfs(t_tbhash *i, short lvl, short len)
{
	short	j;
	short	num_links;
	short	ret;
	short	flag;
	short	ret_fill;

	j = 0;
	flag = 0;
	num_links = i->num_links;
	if (num_links == 0 || len > g_ways.num_rooms - 1 || i->flag == 1 ||
		g_ways.way + 1 > g_ways.num_rooms * 10)
		return (-1);
	ret_fill = g_ways.way;
	g_ways.ways[g_ways.way][i->place_mtrx] = lvl;
	if (i->p_y == 0)
		return (final_room(&g_ways, lvl, i, len));
	else
	{
		i->flag = 1;
		while (num_links > 0 && i->num_links > 0)
		{
			num_links > i->num_links ? num_links = i->num_links : 0;
			if (i->links[j] != NULL)
			{
				if (i->links[j]->flag != 1 &&
				i->links[j]->p_x >= i->p_x + BIG_MAP &&
				(i->links[j]->p_x > 1 || i->p_x == 0))
					ret = dfs(i->links[j], lvl, len + (short)1);
				else
					ret = -1;
				if (ret == -2 || ret == -4)
					flag++;
				i->p_x == 0 ? lvl++ : 0;
				num_links--;
			}
			j++;
		}
		i->flag = 0;
	}
	if (flag > 0 && i->p_x != 0)
		return (insert_room(&g_ways, ret_fill, lvl, i));
	return (del_way(g_ways.way, ret_fill, g_ways.ways, i->place_mtrx));
}

short		**prep_dfs(t_tbhash **th, t_mtrx *mtrx, int num_a_r[2])
{
	int			i;
	const short	num_links = (short)(START->num_links + 1);

	g_ways.way = 0;
	g_ways.num_rooms = num_a_r[1];
	g_ways.diff = (short)(mtrx->total_links - mtrx->num_a_r[1]);
	CH_NULL(g_ways.ways = (short **)malloc(sizeof(short *) * (num_a_r[1] * 10 +
			1)));
	i = -1;
	CH_NULL(mtrx->num_lvls = (short *)ft_memalloc(sizeof(short) *
			(num_links + 1)));
	CH_NULL(mtrx->final_ways = (short **)ft_memalloc(sizeof(short *) *
			(num_links)));
	CH_NULL(mtrx->baned_lvls = (short *)ft_memalloc(sizeof(short) *
			(START->num_links + 1)));
	while (++i < (num_a_r[1] * 10 + 1))
		CH_NULL(g_ways.ways[i] = (short *)ft_memalloc(sizeof(short) *
				(num_a_r[1] + 1)));
	dfs(START, 1, 0);
	g_ways.ways[0][START->place_mtrx] = 0;
	mtrx->ways = g_ways.ways;
	mtrx->num_ways = g_ways.way;
	return (g_ways.ways);
}
