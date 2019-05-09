/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_force.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:59:44 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/09 15:04:25 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static short	**g_final_ways;
static short	**g_ways;
static short	*g_num_lvls;
static short	*g_baned_lvls;
static int		g_len;
static short	g_bad_lvl;

static void line_print(short *line)
{
	int i = -1;
	if (line == NULL)
		return ;
	while (++i < g_len)
		if (line[i] != 0)
			ft_printf("%2d", line[i]);
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

short		brute_force(short *prev_line,  short lvl, short len)
{
	short *line;
	short i;
	short j;
	short ret;

	ret = -1;
	if (lvl == 14)
		ft_printf("");
	if (g_num_lvls[lvl] == -1)
	{
		ft_printf(YELLOW"final way ! \n");
		line_print(prev_line);
		ft_printf("\n"REBOOT);
		return (0);
	}
	else if (g_baned_lvls[lvl] == 1 || g_num_lvls[lvl] == 0)
		return (brute_force(prev_line, lvl + (short)1, len));
	j = lvl - (short)1;
	while (j > 0 && g_num_lvls[j] == 0)
		j--;
	i = g_num_lvls[j];
	while (i < g_num_lvls[lvl])
	{
		CH_NULL(line = (short *)malloc(sizeof(short) * g_len));
		shortcpy(line, prev_line, (size_t)g_len);
//		line_print(g_ways[i]);
//		ft_printf("[%d]\n", i);

		j = 0;
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
				ft_memdel((void **)&line);
				return (0);
			}
			else
			{
				if (ret != lvl)
				{
					ft_memdel((void **)&line);
					return (ret);
				}
			}
		}
		i++;
	}
	g_bad_lvl < lvl ? g_bad_lvl = lvl : 0;
	return (ret);
}

void print_ways(short **final_ways)
{
	int i;
	int j;

	i = -1;
	ft_printf("\n");
	if (final_ways == NULL)
		return ;
	while (final_ways[++i] != NULL)
	{
		j = -1;
		while (++j < g_len)
//			if (final_ways[i][j] == 0)
//				ft_printf("", final_ways[i][j]);
//			else
				ft_printf(YELLOW"%2d"REBOOT, final_ways[i][j]);
		ft_printf("\n");
	}
}

int calc_lvls(short *g_num_lvls, int num, short **ways, int j);
int count_turns(short **g_final_ways, t_mtrx *ways, short *k);
short **sort_cpy_ways(short **links, int len);

void	 		prep_brute_force(t_tbhash **th, t_mtrx *ways)
{
	short	**ret_ways;
	short	**cpy_ways;
	short	*line;
	short	max_ways;
	short	k;
	short	i;

	g_bad_lvl = -1;
	g_ways = ways->ways;
	g_num_lvls = ways->num_lvls;
	g_len = ways->num_a_r[1] - 1;
	g_final_ways = ways->final_ways;
	g_baned_lvls = ways->baned_lvls;
	CH_NULL(ret_ways = (short **)ft_memalloc(sizeof(short *) *
			(START->num_links + 1)));
	CH_NULL(line = (short *)ft_memalloc(sizeof(short) * g_len));
	calc_lvls(g_num_lvls, ways->num_ways, g_ways, ways->num_a_r[1] - 1);
	sort_lvls_in_mtrx(g_num_lvls, g_ways, ways);
//	print_mtrx(ways, num_a_r[1] + 1);
	max_ways = 0;
	i = -1;
	int j = -1;
	int r = -1;
	int buf = 0;
	int const_buf = 99999999;
//	while (++r < START->num_links + 1)
//	{
//		i = (short)(r - 1);
		while (++i < START->num_links + 1)
		{
			j = r - 1;
			while (++j <= i)
				g_baned_lvls[j] = 1;
			k = -1;
			ft_printf("[%d]", i);
			while (++k < START->num_links + 1)
				ft_printf("%d ", g_baned_lvls[k]);
			ft_printf("\n");
//			brute_force(line, 1, 0);
			while (brute_force(line, 1, 0) != 0)
			{
				ft_printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
				g_baned_lvls[g_bad_lvl] = 1;
				g_bad_lvl = -1;
			}
			//		print_ways();
			cpy_ways = sort_cpy_ways(g_final_ways, ways->num_a_r[1]);
//			print_ways(cpy_ways);
			buf = count_turns(cpy_ways, ways, &k);
			ft_memdel((void **)&cpy_ways);
			if (buf > 0 && buf < const_buf)
			{
				const_buf = buf;
				max_ways = k;
				ret_ways = ft_memcpy(ret_ways, g_final_ways, sizeof(short **) *
						START->num_links + 1);
				print_ways(ret_ways);
			}
			ft_bzero(g_final_ways, sizeof(short **) * START->num_links + 1);
			ft_bzero(g_baned_lvls,
					 sizeof(short) * (size_t) START->num_links + 1);
		}
//	}
	ways->final_ways = ret_ways;
	print_ways(ret_ways);
	ft_memdel((void **)&line);
	ft_memdel((void **)&g_final_ways);
	ways->num_ways = max_ways;
//	print_mtrx(ways, num_a_r[1] + 1);
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
	ft_printf("len way = %d\n", final_ways[0][ways->num_a_r[1]]);
	buf = dstrbtd_ants[0] + final_ways[0][ways->num_a_r[1]];
	ft_memdel((void **)&dstrbtd_ants);
//	*k = 1;
//	if (*g_final_ways == NULL)
//		return (0);
//	if (g_final_ways[1] == NULL)
//		return (ways->num_a_r[0] + g_final_ways[0][ways->num_a_r[1]]);
//	buf = 0;
//	while (g_final_ways[*k] != NULL)
//	{
////		len_way = g_final_ways[k][ways->num_a_r[1]];
//		buf += (g_final_ways[*k][ways->num_a_r[1]] -
//				g_final_ways[*k - 1][ways->num_a_r[1]]) * *k;
//		*k += 1;
//	}
//	buf = (ways->num_a_r[0] + buf) / *k + g_final_ways[0][ways->num_a_r[1]];
	return (buf);
}

short **sort_cpy_ways(short **links, int len)
{
	short i;
	short j;
	short **cpy_links;

	i = 0;
	while (links[i] != NULL)
		i++;
	if (i == 0)
		return (NULL);
	CH_NULL(cpy_links = (short **)malloc(sizeof(short *) * (i + 1)));
	ft_memcpy(cpy_links, links, sizeof(short **) * (i + 1));
	i = -1;
	while (cpy_links[++i + 1] != NULL)
	{
		j = i;
		while (j > -1 && cpy_links[j][len] > cpy_links[j + 1][len])
		{
			ft_swap((void **)cpy_links + j, (void **)cpy_links + j + 1);
			j--;
		}
	}
	return (cpy_links);
}

int calc_lvls(short *g_num_lvls, int num, short **ways, int j)
{
	int i;
	int k;
	int l;

	i = -1;
	k = 1;
	g_num_lvls[num - 1] = -1;
	while (++i < num)
	{
		if (ways[i][j] == 0)
			continue ;
//		ft_printf("%d\n", ways[i][j]);
		if (k > 0 && ways[i][j] != 0 && k != ways[i][j])
		{
			l = k;
			while (k > 1 && g_num_lvls[l] == 0)
				l--;
//			ft_printf("l = %d : %d\n", l, g_num_lvls[l]);
			g_num_lvls[ways[i][j]] = g_num_lvls[l];
			k = ways[i][j];
		}
		g_num_lvls[ways[i][j]] += 1;
	}
	if (num > 0)
		g_num_lvls[ways[num - 1][j] + 1] = -1;
	i = -1;
	ft_printf("\n");
	while (++i <= MAX_INT)
		if (g_num_lvls[i] == -1)
			break ;
		else
			ft_printf("lvl = [%d] : %d\n", i, g_num_lvls[i]);
	ft_printf("lvl = [%d] : %d\n", i, g_num_lvls[i]);
	ft_printf("\n");
//	g_num_lvls[0] = 1;
	return (i);
}
