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

static short	**g_final_ways;
static short	**g_ways;
static short	*g_num_lvls;
static short	*g_baned_lvls;
static int		g_len;
static short	g_total_ways;
static t_mtrx	*g_mtrx;
static int		const_buf;
static int		max_ways;
static short	**ret_ways;
static t_tbhash	*start;

int calc_lvls(short *num_lvls, int num, short **ways, int j)
{
	int i;
	int k;
	int l;

	i = -1;
	k = 1;
	num_lvls[num - 1] = -1;
	while (++i < num)
	{
		if (ways[i][j] == 0)
			continue ;
		if (k > 0 && ways[i][j] != 0 && k != ways[i][j])
		{
			l = k;
			while (k > 1 && num_lvls[l] == 0)
				l--;
			num_lvls[ways[i][j]] = num_lvls[l];
			k = ways[i][j];
		}
		num_lvls[ways[i][j]] += 1;
	}
	if (num > 0)
		num_lvls[ways[num - 1][j] + 1] = -1;
	i = -1;
	return (i);
}

int count_turns(short **final_ways, t_mtrx *ways, short *k)
{
	int buf;
	int *dstrbtd_ants;

	if (final_ways == NULL || *final_ways == NULL)
		return (MAX_INT);
	*k = 0;
	while (final_ways[*k] != NULL)
		*k += 1;
	if ((dstrbtd_ants = find_num_ants(ways->num_a_r[0], final_ways, *k,
									  ways->num_a_r[1])) == NULL)
		return (MAX_INT);
	buf = dstrbtd_ants[0] + final_ways[0][ways->num_a_r[1]];
	ft_memdel((void **)&dstrbtd_ants);
	return (buf);
}

void shortcpy(short *dst, short *src, size_t len)
{
	size_t

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

short		brute_force(short *prev_line,  short i, short len)
{
	short *line;
	short j;
	int buf = 0;
	short k;
	short flag = 0;

	if (len > start->num_links)
		return (0);
	CH_NULL(line = (short *)malloc(sizeof(short) * g_len));
	j = 0;
	while (i < g_total_ways)
	{
		if (g_baned_lvls[g_ways[i][g_len]] == 1)
		{
			i++;
			continue ;
		}
		j = 0;
		shortcpy(line, prev_line, (size_t)g_len);
		while (++j < g_len)
			if (g_ways[i][j] != 0)
			{
				if (line[j] == 0)
					line[j] = g_ways[i][j];
				else
					break ;
			}
		if (j == g_len)
		{
			flag++;
			g_baned_lvls[g_ways[i][g_len]] = 1;
//			ft_printf("%d \n", g_ways[i][g_len]);
			g_final_ways[len] = g_ways[i];
			brute_force(line, i + 1, len + (short)1);
			g_final_ways[len] = NULL;
			g_baned_lvls[g_ways[i][g_len]] = 0;
			if (len > 0 && i > (g_total_ways * 4 > 500 ? 32 : 1)) //32
			{
				ft_memdel((void **)&line);
				return (0);
			}
		}
		i++;
	}
	if (i == g_total_ways)
	{
		buf = count_turns(g_final_ways, g_mtrx, &k);
		if (buf > 0 && buf < const_buf)
		{
			const_buf = buf;
			max_ways = k;
			ft_memcpy(ret_ways, g_final_ways, sizeof(short *) *
					(start->num_links + 1));
		}
	}
	ft_memdel((void **)&line);
	return (0);
}

void	 		prep_brute_force(t_tbhash **th, t_mtrx *ways)
{
	short	*line;

	ft_printf(PURPLE"NUW WAYS = %d\n"REBOOT, ways->num_ways);
	g_total_ways = ways->num_ways;
	if (ways->num_ways > 400 && ways->num_ways < 500)
		g_total_ways = (g_total_ways / 3);
	else if (ways->num_ways > 499 && ways->num_ways < 1000)
		g_total_ways = (g_total_ways / 4);
	else if (ways->num_ways > 999)
		g_total_ways = (g_total_ways / 8);
	ft_printf(PURPLE"NUW WAYS = %d\n"REBOOT, g_total_ways);
	g_ways = ways->ways;
	g_num_lvls = ways->num_lvls;
	g_len = ways->num_a_r[1] - 1;
	g_final_ways = ways->final_ways;
	g_baned_lvls = ways->baned_lvls;
	g_mtrx = ways;
	start = START;
	CH_NULL(ret_ways = (short **)ft_memalloc(sizeof(short *) *
			(START->num_links + 1)));
	CH_NULL(line = (short *)ft_memalloc(sizeof(short) * g_len));
	calc_lvls(g_num_lvls, ways->num_ways, g_ways, ways->num_a_r[1] - 1);
	shells_sort(g_ways, ways->num_ways - 1, ways->num_ways / 2,
			ways->num_a_r[1]);
	max_ways = 0;
	const_buf = MAX_INT;
	brute_force(line, 0, 0);
	ways->final_ways = ret_ways;
	ft_memdel((void **)&line);
	ft_memdel((void **)&g_final_ways);
	ways->num_ways = max_ways;
}
