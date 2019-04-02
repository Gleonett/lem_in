/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:14:32 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	choose_type_arg(va_list start, va_list dest, int *j)
{
	t_print	*cursor;

	cursor = g_start_list;
	if (g_mod->prec_num_arg != -1)
	{
		if (find_d_dd() == 0)
			va_arg_num_int(start, g_mod->prec_num_arg, &(g_mod)->precision);
		else
		{
			while (++*j != g_mod->prec_num_arg && cursor != NULL)
			{
				if (IF_D_DD(cursor->type) != 0)
					(void)va_arg(dest, long double);
				else
					(void)va_arg(dest, void *);
				cursor = cursor->next;
			}
			va_arg_num_int(start, g_mod->prec_num_arg - *j,
					&(g_mod)->precision);
		}
	}
}

void		va_arg_precision(va_list start, va_list ap)
{
	va_list	dest;
	int		j;

	if (g_mod->prec_num_arg == 0 && g_mod->precision < 0)
	{
		g_mod->precision = va_arg(ap, int);
		return ;
	}
	j = 0;
	va_copy(dest, start);
	choose_type_arg(start, dest, &j);
	if (g_mod->precision < 0 && g_mod->precision != -1)
		g_mod->precision = 0;
	va_end(dest);
}
