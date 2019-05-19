/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution_ants.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:53:37 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/09 17:10:27 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short **g_final_ways_short;
static char **g_final_ways;
static long long int g_num_way;
static int g_i;

void		search_rooms(t_tbhash *i)
{
	short k;

	if (i == NULL)
		return ;
	if (i->p_y == 0)
	{
		g_final_ways[g_i++] = i->room;
		return ;
	}
	k = -1;
	while (++k < i->num_links)
	{
		if ((i->links[k]->p_y == 0 ||
		g_final_ways_short[g_num_way][i->links[k]->place_mtrx] != 0))
		{
			g_final_ways[g_i++] = i->room;
			g_final_ways_short[g_num_way][i->links[k]->place_mtrx] = 0;
			search_rooms(i->links[k]);
			return ;
		}
	}
}

t_tbhash	*get_ways(t_tbhash *start, t_mtrx *mtrx, char ***final_ways)
{
	short i;

	i = -1;
	g_i = 0;
	g_num_way = -1;
	g_final_ways_short = mtrx->final_ways;
	while (++g_num_way < mtrx->num_ways)
	{
		i = -1;
		g_final_ways = final_ways[g_num_way];
		while (++i < mtrx->final_ways[g_num_way][mtrx->num_a_r[1] - 1])
			;
		search_rooms(start->links[i - 1]);
		g_i = 0;
	}
	return (start->links[i]);
}

void		sort_final_ways(short **links, char ***final_ways, short num,
				int len)
{
	short i;
	short j;

	i = -1;
	while (++i + 1 < num)
	{
		j = i;
		while (j > -1 && links[j][len] > links[j + 1][len])
		{
			ft_swap((void **)links + j, (void **)links + j + 1);
			ft_swap((void **)final_ways + j, (void **)final_ways + j + 1);
			j--;
		}
	}
}

void		distribution_ants(t_tbhash **th, t_mtrx *mtrx)
{
	char	***final_ways;
	short	i;

	CH_NULL(final_ways = (char ***)malloc(sizeof(char **) *
			(mtrx->num_ways + 1)));
	final_ways[mtrx->num_ways] = NULL;
	i = -1;
	while (++i < mtrx->num_ways)
		CH_NULL(final_ways[i] = (char **)ft_memalloc(sizeof(char *) *
				(mtrx->final_ways[mtrx->num_ways - 1][mtrx->num_a_r[1]] + 3)));
	get_ways(START, mtrx, final_ways);
	sort_final_ways(mtrx->final_ways, final_ways, mtrx->num_ways,
			mtrx->num_a_r[1]);
	print_ants(final_ways, mtrx);
	i = -1;
	while (++i < mtrx->num_ways)
		ft_memdel((void **)final_ways + i);
	ft_memdel((void **)&final_ways);
}
