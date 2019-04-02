/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:06:06 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/09 16:54:15 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	choose_type_dd(va_list ap, va_list start, long double *var_dd,
							void **p)
{
	if (g_mod->type == 11 || g_mod->type == 41 || g_mod->type == 42 ||
			g_mod->type == 48 || g_mod->type == 51)
	{
		if (g_mod->num_arg == 0)
			*var_dd = va_arg(ap, long double);
		else
			va_arg_num_dd(start, g_mod->num_arg, var_dd);
	}
	else
	{
		if (g_mod->num_arg == 0 && g_mod->type < 106)
			*p = va_arg(ap, void *);
		else if (g_mod->type < 106)
			va_arg_num(start, g_mod->num_arg, p);
	}
}

static int	choose_type_d(va_list ap, va_list start, double *var_d)
{
	if (g_mod->type == 10 || g_mod->type == 24 || g_mod->type == 37 ||
			g_mod->type == 38 || g_mod->type == 43 || g_mod->type == 46 ||
			g_mod->type == 49)
	{
		if (g_mod->num_arg == 0)
			*var_d = va_arg(ap, double);
		else
			va_arg_num_d(start, g_mod->num_arg, var_d);
		return (1);
	}
	return (0);
}

int			parser(va_list ap, va_list start)
{
	void		*p;
	int			*spec_n;
	double		var_d;
	long double var_dd;

	p = NULL;
	var_d = 0;
	var_dd = 0;
	if (g_mod->error == 1)
		return (1);
	if (g_mod->type == 4)
		return (print(NULL, 0, 0));
	va_arg_width(start, ap);
	va_arg_precision(start, ap);
	if (choose_type_d(ap, start, &var_d) == 0)
		choose_type_dd(ap, start, &var_dd, &p);
	if (g_mod->type == 62)
	{
		spec_n = p;
		*spec_n = g_output_symbols;
		return (1);
	}
	if (print(&p, var_d, var_dd) == 0)
		return (0);
	return (1);
}
