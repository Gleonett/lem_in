/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_force.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:59:44 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/16 17:54:20 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short	**g_final_ways;
static short	**g_ways;
static short	*g_num_lvls;
static short	*g_baned_lvls;
static int		g_len;
static short	g_bad_lvl;

void line_print(short *line)
{
	int i = -1;
	while (++i < g_len)
		ft_printf("%2d ", line[i]);
}

short		brute_force(short *prev_line,  short lvl, short len)
{
	short *line;
	short i;
	short j;
	short ret;

	ret = -1;
	if (g_baned_lvls[lvl] == 1 || g_num_lvls[lvl] == 0)
		return (brute_force(prev_line, lvl + (short)1, len));
	else if (g_num_lvls[lvl] == -1)
	{
		ft_printf(YELLOW"final way ! \n");
		line_print(prev_line);
		ft_printf("\n"REBOOT);
		return (0);
	}
	i = g_num_lvls[lvl - 1];
	while (i < g_num_lvls[lvl])
	{
		CH_NULL(line = (short *)malloc(sizeof(short) * g_len));
		ft_memcpy(line, prev_line, sizeof(short) * g_len);
//		line_print(line);
//		ft_printf("[%d]\n", i);
		j = -1;
		while (++j < g_len)
			if (g_ways[i] != NULL && g_ways[i][j] != 0)
			{
				if (line[j] == 0)
					line[j] = g_ways[i][j];
				else
				{
					ret = line[j];
					ft_memdel((void **)&line);
					break ;
				}
			}
		if (j == g_len)
		{
			if ((ret = brute_force(line, lvl + (short)1, len + (short)1)) == 0)
			{
				g_final_ways[len] = g_ways[i];
				return (0);
			}
			else
			{
				ft_memdel((void **)&line);
				if (ret != lvl)
					return (ret);
			}
		}
		i++;
	}
	g_bad_lvl < lvl ? g_bad_lvl = lvl : 0;
	return (ret);
}

void print_ways(void)
{
	int i;
	int j;

	i = -1;
	ft_printf("\n");
	while (g_final_ways[++i] != NULL)
	{
		j = -1;
		while (++j < g_len)
			if (g_final_ways[i][j] == 0)
				ft_printf("%2d", g_final_ways[i][j]);
			else
				ft_printf(YELLOW"%2d"REBOOT, g_final_ways[i][j]);
		ft_printf("\n");
	}
}

int calc_lvls(short *g_num_lvls, int num, short **ways, int j);

void	 		prep_brute_force(t_tbhash **th, t_mtrx *ways)
{
	short	*line;

	g_bad_lvl = -1;
	g_ways = ways->ways;
	g_num_lvls = ways->num_lvls;
	g_len = ways->num_a_r[1] - 1;
	g_final_ways = ways->final_ways;
	g_baned_lvls = ways->baned_lvls;
	CH_NULL(line = (short *)ft_memalloc(sizeof(short) * g_len));
	calc_lvls(g_num_lvls, START->num_links + 2, g_ways, ways->num_a_r[1] - 1);
//	print_mtrx(ways, num_a_r[1] + 1);
	while (brute_force(line, 1, 0) != 0)
	{
		printf("--------------------------------------------------\n");
		g_baned_lvls[g_bad_lvl] = 1;
		g_bad_lvl = -1;
	}
	print_ways();
//	print_mtrx(ways, num_a_r[1] + 1);
}



int calc_lvls(short *g_num_lvls, int num, short **ways, int j)
{
	int i;
	int k;

	i = -1;
	k = 0;
	g_num_lvls[num - 1] = -1;
	while (++i < j)
	{
		ft_printf(RED"%d "REBOOT, g_num_lvls[0]);
		ft_printf("%d\n", ways[i][j]);
		if (ways[i][j] == 0)
			continue ;
		if (k != ways[i][j])
			g_num_lvls[ways[i][j]] = g_num_lvls[ways[i][j] - 1];
		k = ways[i][j];
		g_num_lvls[ways[i][j]] += 1;
	}
	i = -1;
	ft_printf("\n");
	while (++i < num)
		ft_printf("%d\n", g_num_lvls[i]);
	ft_printf("\n");
//	g_num_lvls[0] = 1;
	return (i);
}
