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
static short	count_logs;

int calc_lvls(short *g_num_lvls, int num, short **ways, int j);
int count_turns(short **g_final_ways, t_mtrx *ways, short *k);

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
//		len == 0 ? LINE : 0;
		if (g_baned_lvls[g_ways[i][g_len]] == 1)
		{
			i++;
			continue ;
		}
		j = 0;
//		CH_NULL(line = (short *)malloc(sizeof(short) * g_len));
		shortcpy(line, prev_line, (size_t)g_len);
		while (++j < g_len)
			if (g_ways[i][j] != 0)
			{
				if (line[j] == 0)
					line[j] = g_ways[i][j];
				else
					break ;
			}
		if (len == 0)
			ft_printf("");
		if (j == g_len)
		{
			flag++;
			g_baned_lvls[g_ways[i][g_len]] = 1;
//			ft_printf("%d \n", g_ways[i][g_len]);
			g_final_ways[len] = g_ways[i];
			brute_force(line, i + 1, len + (short)1);
			g_final_ways[len] = NULL;
			g_baned_lvls[g_ways[i][g_len]] = 0;
			if (len > 5 || (len < 6 && flag > 3))
			{
				ft_memdel((void **)&line);
				return (0);
			}
		}
		i++;
	}
	if (i == g_total_ways)
	{
//		ft_printf("kek\n");
		buf = count_turns(g_final_ways, g_mtrx, &k);
		if (buf > 0 && buf < const_buf)
		{
			const_buf = buf;
			max_ways = k;
			ft_memcpy(ret_ways, g_final_ways, sizeof(short *) *
					(start->num_links + 1));
//			print_ways(ret_ways);
//			ft_printf("LOOOOOOOOOL\n");
		}
//		ft_printf("%d\n", len);
	}
	ft_memdel((void **)&line);
//	ft_printf(GREEN);
//	LINE;
//	ft_printf(REBOOT);
	return (0);
}

int count_turns(short **g_final_ways, t_mtrx *ways, short *k);
short **sort_cpy_ways(short **links, int len);

void	 		prep_brute_force(t_tbhash **th, t_mtrx *ways)
{
//	short	**ret_ways;
	short	**cpy_ways;
	short	*line;
	short	k;
	short	i;

	g_total_ways = ways->num_ways + 1;
	g_ways = ways->ways;
	g_num_lvls = ways->num_lvls;
	g_len = ways->num_a_r[1] - 1;
	g_final_ways = ways->final_ways;
	g_baned_lvls = ways->baned_lvls;
	g_mtrx = ways;
	count_logs = 0;
	start = START;
//	LINE;
	CH_NULL(ret_ways = (short **)ft_memalloc(sizeof(short *) *
			(START->num_links + 1)));
	CH_NULL(line = (short *)ft_memalloc(sizeof(short) * g_len));
	calc_lvls(g_num_lvls, ways->num_ways, g_ways, ways->num_a_r[1] - 1);
	shells_sort(g_ways, ways->num_ways - 1, ways->num_ways / 2,
			ways->num_a_r[1]);
//	print_mtrx(g_ways, ways->num_a_r[1] + 1, ways->num_ways);
	max_ways = 0;
	const_buf = MAX_INT;
			g_total_ways--;
			brute_force(line, 0, 0);
	ways->final_ways = ret_ways;
//	print_ways(ret_ways);
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
//	ft_printf("len way = %d\n", final_ways[0][ways->num_a_r[1]]);
	buf = dstrbtd_ants[0] + final_ways[0][ways->num_a_r[1]];
	ft_memdel((void **)&dstrbtd_ants);
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
//	ft_printf("\n");
//	while (++i <= MAX_INT)
//		if (g_num_lvls[i] == -1)
//			break ;
//		else
//			ft_printf("lvl = [%d] : %d\n", i, g_num_lvls[i]);
//	ft_printf("lvl = [%d] : %d\n", i, g_num_lvls[i]);
//	ft_printf("\n");
//	g_num_lvls[0] = 1;
	return (i);
}
