/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:39:46 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	del_list(int fail)
{
	t_print *cursor;

	while (g_start_list != NULL)
	{
		cursor = g_start_list->next;
		ft_memdel((void **)(&g_start_list));
		g_start_list = cursor;
	}
	if (fail == -1)
		exit(-1);
}

int		find_d_dd(void)
{
	t_print *cursor;

	cursor = g_start_list;
	while (cursor != g_mod && cursor != NULL)
	{
		if (IF_D_DD(g_mod->type))
			return (1);
		cursor = cursor->next;
	}
	if (IF_D_DD(g_mod->type))
		return (1);
	return (0);
}

t_print	*init_list(void)
{
	t_print *new_list;

	if ((new_list = (t_print *)malloc(sizeof(t_print))) == NULL)
		del_list(-1);
	ft_bzero(new_list->flag, 6);
	new_list->type = -1;
	new_list->width = 0;
	new_list->precision = -1;
	new_list->num_arg = 0;
	new_list->width_num_arg = -1;
	new_list->prec_num_arg = -1;
	new_list->i = 0;
	new_list->error = 0;
	new_list->next = NULL;
	return (new_list);
}
