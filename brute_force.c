/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_force.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:59:44 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/12 20:59:59 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_for_brtfrc g_vars;

static void	new_final_ways(t_in_brtfrc *invars)
{
	g_vars.num_ends++;
	invars->k = 0;
	invars->buf = count_turns(g_vars.final_ways, g_vars.mtrx, &(invars->k));
	if (invars->buf > 0 && invars->buf < g_vars.const_buf)
	{
		g_vars.const_buf = invars->buf;
		g_vars.max_ways = invars->k;
		ft_memcpy(g_vars.ret_ways, g_vars.final_ways, sizeof(short *) *
				((g_vars.start)->num_links + 1));
	}
}

static int	match_ways(t_in_brtfrc *invars, short i)
{
	while (++(invars->j) < g_vars.len)
		if ((g_vars.ways)[i][invars->j] != 0)
		{
			if (invars->line[invars->j] != 0)
				return (0);
			invars->line[invars->j] = (g_vars.ways)[i][invars->j];
		}
	return (0);
}

static int	backtrack(t_in_brtfrc *invars, short i, short len)
{
	(g_vars.final_ways)[len] = NULL;
	(g_vars.baned_lvls)[g_vars.ways[i][g_vars.len]] = 0;
	if (len > 0 && i > (g_vars.total_ways * 4 > 500 ? 32 : 1))
	{
		ft_memdel((void **)&(invars->line));
		return (1);
	}
	return (0);
}

short		brute_force(short *prev_line, short i, short len)
{
	t_in_brtfrc invars;

	invars.flag = 0;
	END_BRT;
	CH_NULL(invars.line = (short *)malloc(sizeof(short) * g_vars.len));
	while (i < g_vars.total_ways)
	{
		SAME_LVL;
		invars.j = 0;
		shortcpy(invars.line, prev_line, (size_t)g_vars.len);
		match_ways(&invars, i);
		if (invars.j == g_vars.len)
		{
			invars.flag++;
			(g_vars.baned_lvls)[(g_vars.ways)[i][g_vars.len]] = 1;
			(g_vars.final_ways)[len] = (g_vars.ways)[i];
			brute_force(invars.line, i + 1, len + (short)1);
			if (backtrack(&invars, i, len) == 1)
				return (0);
		}
		i++;
	}
	i == g_vars.total_ways ? new_final_ways(&invars) : 0;
	ft_memdel((void **)&(invars.line));
	return (0);
}

void		prep_brute_force(t_tbhash **th, t_mtrx *ways)
{
	short	*line;

	g_vars.total_ways = ways->num_ways > 200 ? 170 : ways->num_ways;
	g_vars.ways = ways->ways;
	g_vars.len = ways->num_a_r[1] - 1;
	g_vars.final_ways = ways->final_ways;
	g_vars.baned_lvls = ways->baned_lvls;
	g_vars.mtrx = ways;
	g_vars.start = START;
	CH_NULL(g_vars.ret_ways = (short **)ft_memalloc(sizeof(short *) *
			(START->num_links + 1)));
	CH_NULL(line = (short *)ft_memalloc(sizeof(short) * g_vars.len));
	shells_sort(g_vars.ways, ways->num_ways - 1, ways->num_ways / 2,
			ways->num_a_r[1]);
	g_vars.max_ways = 0;
	g_vars.const_buf = MAX_INT;
	brute_force(line, 0, 0);
	ways->final_ways = g_vars.ret_ways;
	ft_memdel((void **)&line);
	ft_memdel((void **)&(g_vars.final_ways));
	ways->num_ways = g_vars.max_ways;
}
