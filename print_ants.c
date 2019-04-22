/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:12:33 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/22 20:25:59 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void print_dist(int num_ways, int *dstrbtd_ants);

int *find_num_ants(int ants, short **final_ways, short num_ways, int j);

static char	*g_s;
static int	g_i;
static int	*g_ants_in_ways;

void	cpy(char *room, char *ant)
{
	int i;

	i = -1;
	ft_printf("[L%s-%s]", ant, room);
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


int	fill_full_turns(char ***final_ways, char **str_ants, t_mtrx *mtrx,
							int last_ant, int shift)
{
	int i;
	int j;
	int flag;

	i = -1;
	flag = -1;
	if (final_ways[mtrx->num_ways - 1][shift] == NULL)
		return (1);
	while (flag < mtrx->num_ways && last_ant > 0)
	{
		i++;
		j = mtrx->num_ways;
		while (--j > -1)
		{
			if (final_ways[j][shift + i] == NULL)
			{
				flag++;
				last_ant--;
				continue ;
			}
			cpy(final_ways[j][shift + i], str_ants[last_ant--]);
		}
	}
	return (0);
}

int	sharp_beginning(t_d_a *dist_ants, char ***final_ways, char **str_ants,
			int *last_ant, int shift)
{
	int i;
	int j;

	if (dist_ants == NULL)
		return (1);
	i = 1;
	while (dist_ants != NULL)
	{
		j = dist_ants->num_ants_in_turn;
		while (--j > -1)
		{
			if (final_ways[j][shift + i - 1] == NULL)
			{
				*last_ant -= 1;
				continue ;
			}
			cpy(final_ways[j][shift + i - 1], str_ants[(*last_ant)--]);
		}
		dist_ants = dist_ants->dist_ants;
		i++;
	}
	return (i);
}

void	fill_s(char ***final_ways, char **str_ants, t_mtrx *mtrx)
{
	short j;
	int i;
	int turns;
	int last_ant;
	int prev_last_ant;
	t_d_a *start_list;

	last_ant = 0;
	start_list = NULL;
	prev_last_ant = 0;
	turns = 0;
	while (1)
	{
		if (turns + 1 == mtrx->final_ways[0][mtrx->num_a_r[1]])
			return ;
		j = -1;
		while (++j < mtrx->num_ways && g_ants_in_ways[j] > 0)
		{
			g_ants_in_ways[j] -= 1;
			cpy(final_ways[j][0], str_ants[++last_ant]);
		}
		if (j == mtrx->num_ways)
		{
			fill_full_turns(final_ways, str_ants, mtrx,
					prev_last_ant, 1);
		}
		else
		{
			add_start_d_a(&start_list, j);
			i = sharp_beginning(start_list->dist_ants, final_ways, str_ants,
					&prev_last_ant, turns + 1);
			fill_full_turns(final_ways, str_ants, mtrx,
					prev_last_ant, i + turns);
			j == 0 ? turns++ : 0;
		}
		prev_last_ant = last_ant;
		g_s[g_i] = '\n';
		ft_printf("\n");
	}
}

char	**create_del_str_ants(char ***ants, int num_ants, int get_del);

void	print_ants(char ***final_ways, t_mtrx *mtrx)
{
	char	**str_ants;

	g_i = -1;
	CH_NULL(g_s = (char *)malloc((size_t)NUM_SMBLS));
	g_ants_in_ways = find_num_ants(mtrx->num_a_r[0], mtrx->final_ways,
			mtrx->num_ways, mtrx->num_a_r[1]);
	create_del_str_ants(&str_ants, mtrx->num_a_r[0], 0);
	fill_s(final_ways, str_ants, mtrx);
	create_del_str_ants(&str_ants, mtrx->num_a_r[0], 1);
	write(1, g_s, (size_t)g_i);
	ft_memdel((void **)&g_s);
}

char	**create_del_str_ants(char ***ants, int num_ants, int get_del)
{
	int i;

	i = -1;
	if (get_del == 0)
	{
		CH_NULL(*ants = (char **)malloc(sizeof(char *) * num_ants + 1));
		while (++i - 1 < num_ants)
		{
			(*ants)[i] = ft_itoa(i);
//			ft_printf("ant = %s\n", (*ants)[i]);
		}
		return (*ants);
	}
	while (++i - 1 < num_ants)
		ft_memdel((void **)(*ants) + i);
	ft_memdel((void *)ants);
	return (NULL);
}

void print_dist(int num_ways, int *dstrbtd_ants)
{
	int l;
	l = -1;
	LINE;
	while (++l < num_ways)
		ft_printf("[%d] %d\n", l + 1, dstrbtd_ants[l]);
	LINE;
}

int boost(int *dist_ants, int i, int ants, int num_ways)
{
	int j;
	int buf;

	buf = (ants - i) / num_ways;
	j = -1;
	while (++j < num_ways)
		dist_ants[j] += buf;
	buf = (ants - i) % num_ways;
	while (--buf > -1)
		dist_ants[buf] += 1;
	return (1);
}

int *find_num_ants(int ants, short **final_ways, short num_ways, int j)
{
	int *dstrbtd_ants;
	int buf_len;
	int i;
	int k;
	int l;

	CH_NULL(dstrbtd_ants = (int *)ft_memalloc(sizeof(int) * num_ways));
	i = 0;
	dstrbtd_ants[0] = i;
	k = -1;
	while (i < ants && ++k < num_ways)
	{
		if (k > 0)
			buf_len = final_ways[k][j] - final_ways[k - 1][j];
		else
			buf_len = 1;
		if ((i += ((buf_len * (k + 1) - buf_len + 1))) > ants)
		{
			i -= ((buf_len * (k + 1) - buf_len + 1));
			break ;
		}
		l = k;
		dstrbtd_ants[l] = dstrbtd_ants[l] == 0 ? 1 : dstrbtd_ants[l] + 1;
		while (--l > -1)
			dstrbtd_ants[l] += buf_len;
	}
	boost(dstrbtd_ants, i, ants, num_ways);
	print_dist(num_ways, dstrbtd_ants);
	return (dstrbtd_ants);
}
