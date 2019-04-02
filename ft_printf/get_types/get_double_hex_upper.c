/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double_hex_upper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:54:43 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_round_hex(long *temp, int precision)
{
	int			i;
	long		round;
	long double	d_temp;

	if (precision > 0 && precision < 13)
	{
		i = -1;
		round = 16 * 16;
		d_temp = *temp;
		while (++i < precision - 1)
			round *= 16;
		while (d_temp > round)
			d_temp /= 16;
		d_temp = (d_temp + 7.5) / 16;
		*temp = d_temp;
	}
	if (precision == 0)
	{
		while (*temp > 16)
			*temp /= 16;
		if (*temp >= 8)
			*temp = 1;
		else
			*temp = 0;
	}
}

static void	put_null(char *temp_s, int precision)
{
	int i;

	if (precision > 13)
	{
		i = -1;
		while (++i < 13)
			temp_s[i] = temp_s[i + precision - 13];
		while (temp_s[i] != 0)
			temp_s[i++] = '0';
	}
}

static char	*add_mantissa(double arg, char **ret, int sign, int precision)
{
	char	*temp_s;
	long	temp;
	char	*join;

	temp = get_mantissa(arg);
	ft_round_hex(&temp, precision);
	*ret = ft_strdup((sign != 0) ? ("-0X1.") : ("0X1."));
	if (precision == 0)
	{
		(*ret)[(arg < 0) ? 3 : 2] += temp;
		(*ret)[(arg < 0) ? 4 : 3] = 0;
		return (*ret);
	}
	temp_s = ft_strnew((precision == -1) ? (13) : precision);
	symtohex_upper(temp, temp_s, (precision == -1) ? (13) : precision);
	put_null(temp_s, precision);
	join = ft_strjoin(*ret, temp_s);
	ft_strdel(ret);
	ft_strdel(&temp_s);
	*ret = join;
	if (precision == -1)
		*ret = string_cut(ret);
	return (*ret);
}

static char	*add_exponent(double arg, char **ret)
{
	char	*temp_s;
	long	temp;
	char	*join;

	temp = get_exponent(arg) - 1023;
	if (temp < 0)
		join = ft_strjoin(*ret, "P");
	else
		join = ft_strjoin(*ret, "P+");
	ft_strdel(ret);
	*ret = join;
	temp_s = ft_lltoa(temp);
	join = ft_strjoin(*ret, temp_s);
	ft_strdel(ret);
	ft_strdel(&temp_s);
	*ret = join;
	return (*ret);
}

char		*get_double_hex_upper(double arg, int precision)
{
	char	*ret;
	int		sign;

	if ((ret = get_const_double(arg)) != NULL)
		return (ret);
	sign = sign_double(arg);
	if (arg == 0.0)
	{
		if (sign != 0)
			return (ft_strdup("-0X0P+0"));
		else
			return (ft_strdup("0X0P+0"));
	}
	ret = add_mantissa(arg, &ret, sign, precision);
	ret = add_exponent(arg, &ret);
	return (ret);
}
