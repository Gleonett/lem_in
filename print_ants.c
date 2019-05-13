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

void print_dist(int num_ways, int *dstrbtd_ants);

int *find_num_ants(int ants, short **final_ways, short num_ways, int j);

static char	*g_s;
static int	g_i;
static int	*g_ants_in_ways;
static int g_lolololol;

void	cpy(char *room, char *ant)
{
	int i;

	i = -1;
//	ft_printf("%s\n", ant);
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

int	sharp_beginning(t_d_a *dist_ants, char ***final_ways, char **str_ants,
			int last_ant, int shift, short max_num_ways)
{
	int i;
	int j;
	int flag;
	t_d_a *prev_list;

	if (dist_ants == NULL)
		return (1);
	if (shift == 20)
		ft_printf("");
	i = 1;
	flag = 0;
	while (dist_ants != NULL && flag <= dist_ants->num_ants_in_turn)
	{
		j = dist_ants->num_ants_in_turn;
		flag = 0;
		while (--j > -1)
		{
			if (final_ways[j][shift + i] == NULL)
			{
				last_ant -= 1;
				flag++;
				continue ;
			}
			cpy(final_ways[j][shift + i], str_ants[last_ant--]);
		}
		if (dist_ants->num_ants_in_turn == max_num_ways &&
			flag == dist_ants->num_ants_in_turn)
		{
			ft_memdel((void **)&(prev_list->dist_ants));
			return (i == 1 ? -1 : i);
		}
		prev_list = dist_ants;
		dist_ants = dist_ants->dist_ants;
		i++;
	}
	return (i);
}

void	fill_s(char ***final_ways, char **str_ants, t_mtrx *mtrx)
{
	short j;
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
			break ;
		j = -1;
		while (++j < mtrx->num_ways && g_ants_in_ways[j] > 0)
		{
			g_ants_in_ways[j] -= 1;
			cpy(final_ways[j][0], str_ants[++last_ant]);
		}
		add_start_d_a(&start_list, j);
		if (sharp_beginning(start_list->dist_ants, final_ways, str_ants,
				prev_last_ant, turns, mtrx->num_ways) == -1)
			break ;
		j == 0 ? turns++ : 0;
		prev_last_ant = last_ant;
		g_s[g_i] = '\n';
		g_lolololol++;
	}
	del_d_a_list(&start_list);
}

char	**create_del_str_ants(char ***ants, int num_ants, int get_del);

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
	write(1, g_s, (size_t)g_i);
	write(1, "\n", 1);
	ft_printf(GREEN"\n%d - turns\n"REBOOT"%d - rooms\n%d - links\n"
	RED"\nDIFFERENT = %d\n"REBOOT, g_lolololol,
			mtrx->num_a_r[1], mtrx->total_links, mtrx->total_links -
			mtrx->num_a_r[1]);
	ft_memdel((void **)&g_s);
}

char	**create_del_str_ants(char ***ants, int num_ants, int get_del)
{
	int i;

	i = -1;
	if (get_del == 0)
	{
		CH_NULL(*ants = (char **)malloc(sizeof(char *) * (num_ants + 2)));
		while (++i <= num_ants)
		{
			(*ants)[i] = ft_itoa(i);
//			ft_printf("ant = %s\n", (*ants)[i]);
		}
		return (*ants);
	}
	while (++i <= num_ants)
		free((*ants)[i]);
	free(*ants);
	*ants = NULL;
	return (NULL);
}

void print_dist(int num_ways, int *dstrbtd_ants)
{
	int l;
	l = -1;
//	LINE;
	while (++l < num_ways)
		ft_printf("[%d] %d\n", l + 1, dstrbtd_ants[l]);
//	LINE;
}

int *find_num_ants(int ants, short **final_ways, short num_ways, int j)
{
	int *dstrbtd_ants;
	int i;
	int k;

	if (num_ways == 0)
		return (NULL);
	CH_NULL(dstrbtd_ants = (int *)ft_memalloc(sizeof(int) * num_ways));
	i = 1;
	dstrbtd_ants[0] = 0;
	k = 1;
	dstrbtd_ants[0] += 1;
	while (i < ants)
	{
		if (k == num_ways || final_ways[k][j] + dstrbtd_ants[k] >
		final_ways[0][j] + dstrbtd_ants[0] - 1)
		{
			dstrbtd_ants[0] += 1;
			i++;
			k = 1;
//			print_dist(num_ways, dstrbtd_ants);
			continue ;
		}
		dstrbtd_ants[k] += 1;
		i++;
		k++;
	}
//	print_dist(num_ways, dstrbtd_ants);
	return (dstrbtd_ants);
}
