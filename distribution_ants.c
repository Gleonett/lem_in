/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribution_ants.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:53:37 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/21 14:04:12 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short **g_final_ways_short;
static char **g_final_ways;
static short g_num_way;
static short g_i;

void line_print(short *line, short g_len)
{
	int i = -1;
	while (++i < g_len)
		ft_printf("%2d", line[i]);
	ft_printf("\n");
}

void search_rooms(t_tbhash *i)
{
	short j;
	short k;

	if (i->p_y == 0)
	{
		g_final_ways[g_i++] = i->room;
		return ;
	}
	j = -1;
	k = -1;
	while (++k < i->num_links)
	{
		while (i->links[++j] == NULL)
			;
//		line_print(g_final_ways_short[g_num_way], 15);
		if (i->links[j]->p_y == 0 ||
		g_final_ways_short[g_num_way][i->links[j]->place_mtrx] != 0)
		{
			g_final_ways[g_i++] = i->room;
			search_rooms(i->links[j]);
			return ;
		}
	}
}

t_tbhash *get_ways(t_tbhash *start, t_mtrx *mtrx, char ***final_ways)
{
	short i;

	i = -1;
	g_i = 0;
	g_num_way = -1;
	g_final_ways_short = mtrx->final_ways;
	while (++g_num_way < mtrx->num_ways)
	{
		while (start->links[++i] == NULL)
			;
		g_final_ways = final_ways[g_num_way];
		search_rooms(start->links[i]);
		int j = -1;
//		while (++j < g_i)
//			ft_printf("%s ", final_ways[g_num_way][j]);
//		ft_printf("\n");
		g_i = 0;
	}
	return (start->links[i]);
}

void	sort_final_ways(short **links, char ***final_ways, short num, int len)
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

void print_rooms(char ***final_ways, t_mtrx mtrx)
{
	int i;
	int j;

	i = -1;
	while (final_ways[++i] != NULL)
	{
		ft_printf("[%d] ", mtrx.final_ways[i][mtrx.num_a_r[1] - 1]);
		j = -1;
		while (++j < mtrx.final_ways[i][mtrx.num_a_r[1]])
			ft_printf(YELLOW"|"PURPLE"%3s"REBOOT, final_ways[i][j]);
		ft_printf("|\n");
	}
}

void distribution_ants(t_tbhash **th, t_mtrx *mtrx)
{
	char	***final_ways;
	short	i;

	LINE;
	CH_NULL(final_ways = (char ***)malloc(sizeof(char **) *
			(mtrx->num_ways + 1)));
	final_ways[mtrx->num_ways] = NULL;
	i = -1;
	while (++i < mtrx->num_ways)
		CH_NULL(final_ways[i] = (char **)ft_memalloc(sizeof(char *) *
				(mtrx->final_ways[mtrx->num_ways - 1][mtrx->num_a_r[1]] + 1)));
//	sort_final_ways(mtrx->final_ways, final_ways, mtrx->num_ways,
//					mtrx->num_a_r[1]);
	get_ways(START, mtrx, final_ways);
	sort_final_ways(mtrx->final_ways, final_ways, mtrx->num_ways,
			mtrx->num_a_r[1]);
	print_rooms(final_ways, *mtrx);
	print_ants(final_ways, mtrx);
	del_tables(&th);
}