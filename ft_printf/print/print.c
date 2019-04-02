/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 11:01:34 by rwalder-          #+#    #+#             */
/*   Updated: 2019/03/13 15:01:05 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	add_flags(char **output)
{
	t_print *mod;

	mod = g_mod;
	if (mod->type != 4 && mod->type != 10 &&
		mod->type != 11 && mod->type != 24 && mod->type != 52 &&
		!(mod->type >= 37 && mod->type <= 42) &&
		!(mod->type >= 55 && mod->type <= 61))
		make_precision(output);
	make_width(output);
	if (ft_strchr(mod->flag, '#') != NULL)
		make_octotorp(output);
	else if (mod->type != 0 && mod->type != 1 && mod->type != 4 &&
	mod->type != 52 && mod->type != 54 && mod->type >= 3 && mod->type != 4 &&
	mod->type != 6 && mod->type != 8 && mod->type != 9 && mod->type != 14 &&
	mod->type != 16 && mod->type != 17 && mod->type != 20 && mod->type != 22 &&
	mod->type != 23 && mod->type != 27 && mod->type != 29 && mod->type != 30 &&
	mod->type != 33 && mod->type != 35 && mod->type != 36 && mod->type <= 52)
		flags_space_plus(*output, ft_strlen(*output));
	return (1);
}

void		put_thousands_sep(char *output)
{
	int i;
	int j;
	int k;

	i = -1;
	while ((output[++i] == ' ' || output[i] == '0' || output[i] == '+' ||
	output[i] == '-') && output[i] != '\0')
		ft_putnstr_full(output + i, 1);
	j = i;
	while (output[i] != '\0' && output[i] != '.' && output[i] != ' ')
		i++;
	k = ((i - j - 1) % 3) + 1;
	while (output[j] && j != i)
	{
		ft_putnstr_full(output + j, 1);
		if (j++ + 1 == i)
			break ;
		if (--k <= 0)
		{
			ft_putstr_full(",");
			k = 3;
		}
	}
	ft_putstr_full(output + j);
}

static char	*init_output(const void *arg, t_get_output function_get,
		double var_d, long double var_dd)
{
	char *output;

	if (g_mod->error == 2)
	{
		output = ft_strnew(1);
		*output = (char)g_mod->precision;
	}
	else if (IF_OCT(g_mod->type))
		if (g_mod->precision == -1)
		{
			var_d != 0 ? output = function_get(var_d, 6) : 0;
			var_dd != 0 ? output = function_get(var_dd, 6) : 0;
			var_d == 0 && var_dd == 0 ? output = function_get(arg, -1) : 0;
		}
		else
		{
			var_d != 0 ? output = function_get(var_d, g_mod->precision) : 0;
			var_dd != 0 ? output = function_get(var_dd, g_mod->precision) : 0;
			var_d == 0 && var_dd == 0 ?
			output = function_get(arg, g_mod->precision) : 0;
		}
	else
		output = function_get(arg);
	return (output);
}

static int	exceptions(const void *arg, char *output)
{
	t_print *mod;

	mod = g_mod;
	if (ft_strchr(mod->flag, 39) != NULL && (mod->type == 3 || mod->type == 7 ||
	mod->type == 10 || mod->type == 11 || mod->type == 12 || mod->type == 15 ||
	mod->type == 18 || mod->type == 21 || mod->type == 24 || mod->type == 25 ||
	mod->type == 28 || mod->type == 31 || mod->type == 34 || mod->type == 38 ||
	mod->type == 40 || (mod->type >= 42 && mod->type <= 48)))
		PUT_SEP(output);
	else if (mod->type == 0 && mod->error != 2)
	{
		if (mod->width > 1 && output[1] == '0')
			output[mod->width - 1] = *(char *)arg;
		else if (mod->width > 1 && ft_strchr(mod->flag, '-'))
			*output = *(char *)arg;
		else if (mod->width > 1 && ft_strchr(mod->flag, '-') == NULL)
			output[mod->width - 1] = *(char *)arg;
		if (mod->width == 0 || mod->width == -1)
			mod->width = 1;
		ft_putnstr_full(output, (size_t)mod->width);
		return (2);
	}
	return (0);
}

int			print(const void *arg, double var_d, long double var_dd)
{
	t_get_output	function_get;
	char			*output;
	t_print			*mod;
	int				buf;

	mod = g_mod;
	buf = 0;
	if (mod->type > 105)
		return (print_color(mod->type));
	if ((function_get = get_function(mod)) == NULL)
		return (0);
	output = init_output(arg, function_get, var_d, var_dd);
	if (add_flags(&output) == 0)
	{
		ft_strdel(&output);
		return (0);
	}
	if ((buf = exceptions(arg, output)) != 1 && mod->type == 54)
		*output != '\0' ? ft_putstr_full(output) : ft_putnstr_full(output, 1);
	else if (buf != 2)
		ft_putstr_full(output);
	ft_strdel(&output);
	return (1);
}
