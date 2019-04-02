/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_double_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:54:56 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_round_hex(unsigned long *temp, int precision, int *overflow)
{
	int				i;
	unsigned long	round;
	long double		d_temp;

	if (precision >= 0 && precision < 13)
	{
		i = -1;
		round = 16 * 16;
		d_temp = *temp;
		while (++i < precision)
			round *= 16;
		while (d_temp > round)
			d_temp /= 16;
		d_temp = (d_temp + 7.5) / 16;
		*temp = d_temp;
		*overflow = (*temp * 16 >= round) ? (4) : (0);
	}
}

static void	put_null(char **temp_s, int precision)
{
	char	*ret;
	int		i;

	i = -1;
	ret = ft_strnew(precision + 1);
	while ((*temp_s)[++i] != 0 && (i <= precision))
		ret[i] = (*temp_s)[i];
	if (precision > 13)
	{
		while (i <= precision)
			ret[i++] = '0';
		ft_strdel(temp_s);
		*temp_s = ret;
	}
}

static char	*add_mantissa(long double arg, int *overflow, int sign,
		int precision)
{
	char			*temp_s;
	unsigned long	temp;
	char			*join;
	char			*ret;

	if (sign != 0)
		ret = ft_strdup("-0X");
	else
		ret = ft_strdup("0X");
	temp = get_long_mantissa(arg);
	ft_round_hex(&temp, precision, overflow);
	temp_s = get_unsigned_long_long_hex_upper(&temp);
	put_null(&temp_s, precision);
	temp_s = add_comma(&temp_s);
	join = ft_strjoin(ret, temp_s);
	ft_strdel(&ret);
	ft_strdel(&temp_s);
	ret = join;
	if (precision == -1)
		ret = string_cut(&ret);
	return (ret);
}

static char	*add_exponent(long double arg, char **ret, int overflow)
{
	char	*temp_s;
	long	temp;
	char	*join;

	temp = get_long_exponent(arg) - 16386 + overflow;
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

char		*get_long_double_hex_upper(long double arg, int precision)
{
	char	*ret;
	int		sign;
	int		overflow;

	overflow = 0;
	if ((ret = get_const_double_upper(arg)) != NULL)
		return (ret);
	sign = sign_double(arg);
	if (arg == 0.0)
	{
		if (sign != 0)
			return (ft_strdup("-0X0P+0"));
		else
			return (ft_strdup("0X0P+0"));
	}
	ret = add_mantissa(arg, &overflow, sign, precision);
	ret = add_exponent(arg, &ret, overflow);
	return (ret);
}
