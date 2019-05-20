/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharp_beginning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:15:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/14 18:15:22 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_null(char *way, t_printing *prnt, int *flag)
{
	if (way == NULL)
	{
		prnt->last_ant -= 1;
		*flag += 1;
		return (1);
	}
	return (0);
}

int		del_prev_list(t_d_a *prev_list)
{
	if (prev_list == NULL)
		return (1);
	ft_memdel((void **)&(prev_list->dist_ants));
	return (1);
}

void	init_i_flag(t_d_a **prev_list, int *i, int *flag)
{
	*prev_list = NULL;
	*i = 1;
	*flag = 0;
}

int		sharp_beginning(t_d_a *dist_ants, char ***final_ways,
		char **str_ants, t_printing *prnt)
{
	t_d_a	*prev_list;
	int		i;
	int		j;
	int		flag;

	IF_EQUAL_RET(dist_ants, NULL, 1);
	init_i_flag(&prev_list, &i, &flag);
	while (dist_ants != NULL && flag <= dist_ants->num_ants_in_turn)
	{
		j = dist_ants->num_ants_in_turn;
		flag = 0;
		while (--j > -1)
		{
			if (check_null(final_ways[j][prnt->shift + i], prnt, &flag) == 1)
				continue ;
			cpy(final_ways[j][prnt->shift + i], str_ants[prnt->last_ant--]);
		}
		if (dist_ants->num_ants_in_turn == prnt->max_num_ways &&
				flag == dist_ants->num_ants_in_turn)
			return (del_prev_list(prev_list));
		prev_list = dist_ants;
		dist_ants = dist_ants->dist_ants;
		i++;
	}
	return (0);
}
