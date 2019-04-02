/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:20:38 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	choose_type_arg(va_list start, va_list dest, int *j)
{
	t_print	*cursor;

	cursor = g_start_list;
	if (g_mod->width_num_arg != 0 && g_mod->width_num_arg != -1)
	{
		if (find_d_dd() == 0)
			va_arg_num_int(start, g_mod->width_num_arg, &(g_mod)->width);
		else
			while (++*j != g_mod->width_num_arg && cursor != NULL)
			{
				if (IF_D_DD(cursor->type) != 0)
					(void)va_arg(dest, long double);
				else
					(void)va_arg(dest, void *);
				cursor = cursor->next;
				va_arg_num_int(start, g_mod->width_num_arg - *j,
						&(g_mod)->width);
			}
	}
}

void		va_arg_width(va_list start, va_list ap)
{
	va_list	dest;
	int		j;
	int		buf;

	j = -1;
	va_copy(dest, start);
	buf = g_mod->width;
	if (g_mod->width_num_arg == 0)
		g_mod->width = va_arg(ap, int);
	choose_type_arg(start, dest, &j);
	if (g_mod->width < 0)
	{
		j = 0;
		while (g_mod->flag[j] != '0' && g_mod->flag[j] && g_mod->flag[j] != '-')
			j++;
		g_mod->flag[j] = '-';
		g_mod->width <= -2147483648 ? (g_mod->width = 0) : (g_mod->width *= -1);
	}
	if (buf > 0)
		g_mod->width = buf;
	va_end(dest);
}
