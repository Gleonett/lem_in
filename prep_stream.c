/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:38:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/09 18:10:38 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short	**g_ways;
static int		g_way;
static int		g_num_rooms;
static short	g_diff;

short dfs(t_tbhash *i, short lvl, short len)
{
	short	j;
	short	num_links;
	short	ret;
	short 	k;
	short 	flag;
	short	ret_fill;

	j = 0;
	flag = 0;
	num_links = i->num_links;
	if (num_links == 0 || len > g_num_rooms - 1 || i->flag == 1 ||
		g_way + 1 > g_num_rooms * 10)
		return (-1);
//	else if (i->p_y != 0 && g_way != 0)
//	{
//		k = (short)g_way + (short)1;
//		while (--k > -1 && (g_ways[k][g_num_rooms - 1] == lvl ||
//			g_ways[k][g_num_rooms - 1] == 0))
//		{
//
//			if (g_ways[k][i->place_mtrx] == lvl)
//			{
//				if (ft_strcmp("Gyw7", i->room) == 0)
//					printf("");
////				ft_printf("\n");
//				return (-1);
//			}
//		}
//	}
//	ft_printf("%s --> ", i->room);
	ret_fill = g_way;
	g_ways[g_way][i->place_mtrx] = lvl;
	if (i->p_y == 0)
	{
		g_ways[g_way][i->place_mtrx] = 0;
		g_ways[g_way][g_num_rooms - 1] = lvl;
		g_ways[g_way][g_num_rooms] = len;
		g_way++;
//		ft_printf("\n");
		return (-2);
	}
	else
	{
		i->flag = 1;
		while (num_links > 0 && i->num_links > 0)
		{
			if (lvl == 8)
				ft_printf("");
			num_links > i->num_links ? num_links = i->num_links : 0;
			if (i->links[j] != NULL)
			{
				if (i->links[j]->flag != 1 &&
				i->links[j]->p_x >= i->p_x + BIG_MAP &&
				(i->links[j]->p_x > 1 || i->p_x == 0))
//			((i->links[j]->lvl <= i->lvl || i->links[j]->num_links <= 1000)) &&
				{
					ret = dfs(i->links[j], lvl, len + (short)1);
				}
				else
					ret = -1;
				if (ret == -2)
				{
					flag++;
				}
				else if (ret == -4)
					flag++;
//				print_mtrx(g_ways, g_num_rooms + 1);
//				ret = -1;
				i->p_x == 0 ? lvl++ : 0;
				num_links--;
			}
			j++;
		}
		i->flag = 0;
	}
	if (ft_strcmp("8", i->room) == 0)
		ft_printf("");
	if (flag > 0 && i->p_x != 0)
	{

		k = (short)g_way;
//		k = ret == -2 ? g_way : g_way + (short)1;
		while (--k > -1 && k > ret_fill && g_ways[k][g_num_rooms - 1] == lvl)
		{
//			if (g_ways[k][i->place_mtrx] == lvl)
//			{
//				print_mtrx(g_ways, g_num_rooms * 6 + 1);
//				break ;
//			}
			g_ways[k][i->place_mtrx] = lvl;
		}
		return (-4);
	}
//	if (ret == -3 || ret == -1)
//	{
		k = g_way + 1;
		while (--k > -1 && k >= ret_fill)
			g_ways[k][i->place_mtrx] = 0;
//	}
	return (-1);
}

short			**prep_dfs(t_tbhash **th, t_mtrx *mtrx, int num_a_r[2])
{
	int i;
	const short num_links = (short)(START->num_links + 1);

	g_way = 0;
	g_num_rooms = num_a_r[1];
	g_diff = (short)(mtrx->total_links - mtrx->num_a_r[1]);
	CH_NULL(g_ways = (short **)malloc(sizeof(short *) * (num_a_r[1] * 10 +
			1)));
	i = -1;
	CH_NULL(mtrx->num_lvls = (short *)ft_memalloc(sizeof(short) *
			(num_links + 1)));
	CH_NULL(mtrx->final_ways = (short **)ft_memalloc(sizeof(short *) *
			(num_links)));
	CH_NULL(mtrx->baned_lvls = (short *)ft_memalloc(sizeof(short) *
			(num_links + 1)));
	while (++i < (num_a_r[1] * 10 + 1))
		CH_NULL(g_ways[i] = (short *)ft_memalloc(sizeof(short) *
				(num_a_r[1] + 1)));
	mtrx->num_links = num_links;
	dfs(START, 1, 0);
//	ft_printf("\n");
	g_ways[0][START->place_mtrx] = 0;
	mtrx->ways = g_ways;
	mtrx->num_ways = g_way;
//	print_mtrx(g_ways, num_a_r[1] + 1);
//	i = -1;
//	while (++i < num_a_r[1])
//		ft_memdel((void **)g_ways + i);
//	ft_memdel((void **)&g_ways);
	return (g_ways);
}
