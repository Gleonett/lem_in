/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:38:06 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_fmt(const char *fmt, va_list ap, va_list start)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = i;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			ft_putnstr_full(fmt + j, (i - j));
			parser(ap, start);
			i = i + g_mod->i;
			i++;
			j = i;
			g_mod = g_mod->next;
		}
		else
			i++;
	}
	ft_putstr_full(fmt + j);
}

int			ft_printf(const char *fmt, ...)
{
	va_list	ap;
	va_list	start;

	CH_NULL(fmt);
	CH_NULL(g_start_list = init_list());
	g_mod = g_start_list;
	check_fmt(fmt);
	g_output_symbols = 0;
	va_start(ap, fmt);
	va_copy(start, ap);
	put_fmt(fmt, ap, start);
	va_end(start);
	va_end(ap);
	del_list(0);
	return (g_output_symbols);
}
