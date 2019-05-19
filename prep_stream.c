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

static t_for_dfs	g_ways;

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

static int	check_init(t_in_dfs *vars, t_tbhash *i, short lvl, short len)
{
	vars->num_links = i->num_links;
	if (vars->num_links == 0 || len > g_ways.num_rooms - 1 || i->flag == 1 ||
		g_ways.way + 1 > g_ways.num_rooms * 10)
		return (0);
	vars->j = 0;
	vars->flag = 0;
	vars->ret_fill = g_ways.way;
	g_ways.ways[g_ways.way][i->place_mtrx] = lvl;
	return (1);
}

short		dfs(t_tbhash *i, short lvl, short len)
{
	t_in_dfs	vars;

	IF_FALSE(check_init(&vars, i, lvl, len));
	if (i->p_y == 0)
		return (final_room(&g_ways, lvl, i, len));
	else
	{
		i->flag = 1;
		while (vars.num_links > 0 && i->num_links > 0)
		{
			vars.num_links > i->num_links ? vars.num_links = i->num_links : 0;
			if (i->links[vars.j] != NULL)
			{
				vars.ret = CAN_GO_ON ? dfs(i->links[vars.j], lvl, len + 1) : -1;
				vars.ret == -2 || vars.ret == -4 ? vars.flag++ : 0;
				i->p_x == 0 ? lvl++ : 0;
				vars.num_links--;
			}
			vars.j++;
		}
		i->flag = 0;
	}
	if (vars.flag > 0 && i->p_x != 0)
		return (insert_room(&g_ways, vars.ret_fill, lvl, i));
	return (zero_way(g_ways.way, vars.ret_fill, g_ways.ways, i->place_mtrx));
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
	CH_NULL(mtrx->final_ways = (short **)ft_memalloc(sizeof(short *) *
			(num_links)));
	CH_NULL(mtrx->baned_lvls = (short *)ft_memalloc(sizeof(short) *
			(START->num_links + 1)));
	i = -1;
	while (++i < (num_a_r[1] * 10 + 1))
		CH_NULL((g_ways).ways[i] = (short *)ft_memalloc(sizeof(short) *
				(num_a_r[1] + 1)));
	dfs(START, 1, 0);
	g_ways.ways[0][START->place_mtrx] = 0;
	mtrx->ways = g_ways.ways;
	mtrx->num_ways = g_ways.way;
	return (g_ways.ways);
}
