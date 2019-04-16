/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:38:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/16 17:57:21 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short	**g_ways;
static short	g_way;
static int		g_num_rooms;

short dfs(t_tbhash *i, short lvl, short len)
{
	short	j;
	short	num_links;
	short	ret;
	short 	k;
	int		flag;

	flag = 0;
	j = 0;
	ret = -1;
	num_links = i->num_links;
	if (num_links == 0)
		return (1);
	else if (i->p_y != 0 && g_way != 0)
	{
		k = g_way + (short)1;
		while (--k > -1 && (g_ways[k][g_num_rooms - 1] == lvl ||
		g_ways[k][g_num_rooms - 1] == 0))
		{
			if (g_ways[k][i->place_mtrx] == lvl)
			{
//				ft_printf("\n");
				return (3);
			}
		}
	}
//	ft_printf("%s --> ", i->room);
	g_ways[g_way][i->place_mtrx] = lvl;
	if (i->p_y == 0)
	{
		g_ways[g_way][i->place_mtrx] = 0;
		g_ways[g_way][g_num_rooms - 1] = lvl;
		g_ways[g_way][g_num_rooms] = len;
//		ft_printf("\n");
		return (2);
	}
	else
	{
		i->flag = 1;
		while (num_links > 0 && i->num_links > 0)
		{
			num_links > i->num_links ? num_links = i->num_links : 0;
			if (i->links[j] != NULL)
			{
				if (i->links[j]->flag != 1 &&
				(ret = dfs(i->links[j], lvl, len + (short)1)) == 1)
				{
					i->links[j]->flag = 0;
					i->links[j] = NULL;
					i->num_links -= 1;
					if (i->num_links == 0)
						return (1);
				}
				else if (ret == 2)
					num_links - 1 > 0 ? g_way++ : 0;
				ret != 1 ? flag = 1 : 0;
				i->p_x == 0 ? lvl++ : 0;
				num_links--;
			}
			j++;
		}
		i->flag = 0;
	}
//	if (i->num_links > 0)
//		g_ways[g_way][i->place_mtrx] = 0;
	if (flag == 1)
	{
		if (ret != 2)
			return (4);
		k = g_way;
		while (--k > -1 && g_ways[k][g_num_rooms - 1] == lvl)
		{
			if (g_ways[k][i->place_mtrx] == lvl)
				break ;
		}
		if (k > -1 && g_ways[k][i->place_mtrx] == lvl)
		{
			while (g_ways[k][g_num_rooms - 1] == lvl)
				g_ways[k++][i->place_mtrx] = lvl;
		}
		return (2);
	}
	return (ret);
}

short			**prep_dfs(t_tbhash **th, t_mtrx *mtrx, int num_a_r[2])
{
	short i;

	g_way = 0;
	g_num_rooms = num_a_r[1];
	CH_NULL(g_ways = (short **)malloc(sizeof(short *) * (num_a_r[1] + 1)));
	i = -1;
	while (++i < num_a_r[1] + 1)
		CH_NULL(g_ways[i] = (short *)ft_memalloc(sizeof(short) *
				(num_a_r[1] + 1)));
	dfs(START, 1, 0);
	ft_printf("\n");
	g_ways[0][START->place_mtrx] = 0;
	mtrx->ways = g_ways;
	CH_NULL(mtrx->num_lvls = (short *)ft_memalloc(sizeof(short) *
			(START->num_links + 2)));
	CH_NULL(mtrx->final_ways = (short **)ft_memalloc(sizeof(short *) *
			(START->num_links + 1)));
	CH_NULL(mtrx->baned_lvls = (short *)ft_memalloc(sizeof(short) *
			(START->num_links + 2)));
//	print_mtrx(g_ways, num_a_r[1] + 1);
//	i = -1;
//	while (++i < num_a_r[1])
//		ft_memdel((void **)g_ways + i);
//	ft_memdel((void **)&g_ways);
	return (g_ways);
}
