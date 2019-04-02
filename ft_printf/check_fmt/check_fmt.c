/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 14:20:20 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/13 16:27:56 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_width(t_print *g_mod, const char *fmt, size_t *i)
{
	int j;

	j = 0;
	if (fmt[*i] > '0' && fmt[*i] <= '9')
	{
		g_mod->width = ft_atoi(fmt + *i);
		while (fmt[*i] >= '0' && fmt[*i] <= '9')
			*i += 1;
	}
	else
		g_mod->width = 0;
	if (fmt[*i] == '*')
	{
		*i += 1;
		g_mod->width_num_arg = number_of_argument(fmt, i);
		j++;
	}
	if (fmt[*i] > '0' && fmt[*i] <= '9')
	{
		g_mod->width = ft_atoi(fmt + *i);
		while (fmt[*i] >= '0' && fmt[*i] <= '9')
			*i += 1;
	}
	else if (j > 0)
		g_mod->width = 0;
}

static void	check_precision(t_print *g_mod, const char *fmt, size_t *i)
{
	if (fmt[*i] == '.')
		while (fmt[*i] == '.')
		{
			if (fmt[*i + 1] == '.')
				*i += 1;
			*i += 1;
			if (fmt[*i] >= '0' && fmt[*i] <= '9')
			{
				g_mod->precision = ft_atoi(fmt + *i);
				while (fmt[*i] >= '0' && fmt[*i] <= '9')
					*i += 1;
			}
			else
			{
				if (fmt[*i] == '*')
				{
					*i += 1;
					g_mod->prec_num_arg = number_of_argument(fmt, i);
				}
				else
					g_mod->precision = 0;
			}
		}
	else
		g_mod->precision = -1;
}

static const char g_spc[][8] = {
	"c", "s", "p", "i", "%", "d", "o", "u", "x",
	"X", "f", "Lf", "hhd", "hhi", "hho", "hhu", "hhx",
	"hhX", "hd", "hi", "ho", "hu", "hx", "hX", "lf", "ld",
	"li", "lo", "lu", "lx", "lX", "lld", "lli", "llo",
	"llu", "llx", "llX", "e", "g", "le", "lg", "Le", "Lg",
	"G", "lG", "LG", "F", "lF", "LF", "E", "lE", "LE", "S",
	"ls", "C", "lc", "a", "la", "La", "A", "lA", "LA", "n",
	"D", "O", "U", "zu", "zi", "ju", "ji", "jx", "b", "hb",
	"hhb", "lb", "llb", "k", "r", "jd", "zd", "hU", "lO",
	"lU", "lD", "llO", "hO", "hD", "hhO", "hhU", "hhD",
	"hhC", "hhS", "jo", "jX", "jO", "zo", "zx", "zX", "zO",
	"lp", "llU", "llD", "jU", "jD", "zU", "zD", ""
};

static int	check_specif(t_print *g_mod, const char *fmt, size_t *i)
{
	int		j;
	char	ret[20];

	j = 0;
	ft_bzero(ret, 20);
	check_type(fmt, ret, i);
	if (*ret == '{' || *ret == '}')
		return (choose_color(fmt, i, &j));
	else
		while (ft_strcmp(ret, g_spc[j]) != 0)
			j++;
	if (j > 105 && g_mod->width < 2)
		return (1);
	else if (j == 106)
	{
		g_mod->type = 0;
		g_mod->precision = fmt[*i];
		*i += 1;
		g_mod->error = 2;
		return (0);
	}
	choose_size_type(j);
	return (0);
}

int			check_fmt(const char *fmt)
{
	size_t i;
	size_t j;

	i = 0;
	while (fmt[i] != '\0')
		if (fmt[i] == '%')
		{
			i++;
			j = i;
			check_flags(g_mod, fmt, &i);
			check_width(g_mod, fmt, &i);
			check_flags(g_mod, fmt, &i);
			check_precision(g_mod, fmt, &i);
			check_flags(g_mod, fmt, &i);
			CH_ERROR(check_specif(g_mod, fmt, &i));
			clean_flags(g_mod);
			g_mod->i = i - j;
			g_mod->next = init_list();
			g_mod = g_mod->next;
		}
		else
			i++;
	g_mod = g_start_list;
	return (0);
}
