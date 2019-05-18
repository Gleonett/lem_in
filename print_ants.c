/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:12:33 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/12 20:19:39 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*g_s;
static int	g_i;
static int	*g_ants_in_ways;
static int g_lolololol;

void	cpy(char *room, char *ant)
{
	int i;

	i = -1;
	g_s[++g_i] = 'L';
	while (ant[++i])
	{
		if (g_i + 2 > NUM_SMBLS)
		{
			write(1, g_s, (size_t)g_i + 1);
			g_i = -1;
		}
		g_s[++g_i] = ant[i];
	}
	g_s[++g_i] = '-';
	i = -1;
	while (room[++i])
	{
		if (g_i + 4 > NUM_SMBLS)
		{
			write(1, g_s, (size_t)g_i + 1);
			g_i = -1;
		}
		g_s[++g_i] = room[i];
	}
	g_s[++g_i] = ' ';
}

void	init_variables(t_d_a **start_list, t_printing *prnt, int *last_ant,
		short num_ways)
{
	*last_ant = 0;
	*start_list = NULL;
	prnt->last_ant = 0;
	prnt->shift = 0;
	prnt->max_num_ways = num_ways;
}

void	fill_s(char ***final_ways, char **str_ants, t_mtrx *mtrx)
{
	t_d_a		*start_list;
	t_printing	prnt;
	short		j;
	int			last_ant;

	init_variables(&start_list, &prnt, &last_ant, mtrx->num_ways);
	while (1)
	{
		if (prnt.shift + 1 == mtrx->final_ways[0][mtrx->num_a_r[1]] &&
			last_ant == mtrx->num_a_r[0])
			break ;
		j = -1;
		while (++j < prnt.max_num_ways && g_ants_in_ways[j] > 0)
		{
			g_ants_in_ways[j] -= 1;
			cpy(final_ways[j][0], str_ants[++last_ant]);
		}
		add_start_d_a(&start_list, j);
		IF_EQ_BRK(sharp_beginning(start_list->dist_ants,
				final_ways, str_ants, &prnt), -1);
		j == 0 ? prnt.shift += 1 : 0;
		prnt.last_ant = last_ant;
		g_s[g_i] = '\n';
		g_lolololol++;
	}
	del_d_a_list(&start_list);
}

void	print_ants(char ***final_ways, t_mtrx *mtrx)
{
	char	**str_ants;

	g_i = -1;
	g_lolololol = 0;
	CH_NULL(g_s = (char *)malloc((size_t)NUM_SMBLS));
	g_ants_in_ways = find_num_ants(mtrx->num_a_r[0], mtrx->final_ways,
			mtrx->num_ways, mtrx->num_a_r[1]);
	create_del_str_ants(&str_ants, mtrx->num_a_r[0], 0);
	fill_s(final_ways, str_ants, mtrx);
	create_del_str_ants(&str_ants, mtrx->num_a_r[0], 1);
//	write(1, g_s, (size_t)g_i);
	write(1, "\n", 1);
	ft_printf(GREEN"\n%d - turns\n"REBOOT"%d - rooms\n%d - links\n"
	RED"\nDIFFERENT = %d\n"REBOOT, g_lolololol,
			mtrx->num_a_r[1], mtrx->total_links, mtrx->total_links -
			mtrx->num_a_r[1]);
	ft_memdel((void **)&g_s);
}
