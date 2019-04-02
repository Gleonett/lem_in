/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_g_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:27:56 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 18:05:23 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_exp(long double val, unsigned int precision)
{
	val = (val >= 0) ? val : (val * -1);
	if (precision == 0)
	{
		if ((val > 1e-4 && val < 10) || val == 0.0)
			return (0);
		return (1);
	}
	if ((val + 0.5 >= 1e6 || val < 1e-4) && val != 0.0)
		return (1);
	return (0);
}

char		*handle_exp(long double arg, unsigned int precision)
{
	int		i;
	int		exp;
	char	*temp;
	char	*ret;
	char	*join;

	temp = get_long_double_exp(arg, (precision == 0) ? (0) : (precision - 1));
	i = ft_strlen(temp) - 1;
	while (temp[i] != 'e')
		i--;
	exp = i--;
	while (temp[i] == '0')
		i--;
	if (temp[i] == '.')
		i--;
	ret = ft_strsub(temp, 0, i + 1);
	join = ft_strsub(temp, exp, ft_strlen(temp) - exp);
	ft_strdel(&temp);
	temp = ft_strjoin(ret, join);
	ft_strdel(&ret);
	ft_strdel(&join);
	ret = temp;
	return (ret);
}

char		*handle_exp_upper(long double arg, unsigned int precision)
{
	int		i;
	int		exp;
	char	*temp;
	char	*ret;
	char	*join;

	temp = get_long_double_exp_upper(arg, (precision == 0) ? (0) : (precision -
	1));
	i = ft_strlen(temp) - 1;
	while (temp[i] != 'E')
		i--;
	exp = i--;
	while (temp[i] == '0')
		i--;
	if (temp[i] == '.')
		i--;
	ret = ft_strsub(temp, 0, i + 1);
	join = ft_strsub(temp, exp, ft_strlen(temp) - exp);
	ft_strdel(&temp);
	temp = ft_strjoin(ret, join);
	ft_strdel(&ret);
	ft_strdel(&join);
	ret = temp;
	return (ret);
}

static char	*get_norme_value(long double arg, unsigned int precision)
{
	long double val;
	char		*ret;

	if (((arg < 0) ? (arg * -1) : (arg)) < 1.0)
	{
		val = ((arg < 0) ? (arg * -1) : (arg));
		while (val < 1.0 && val != 0.0)
		{
			val *= 10;
			precision++;
		}
		ret = get_long_double(arg, precision);
	}
	else
	{
		val = arg - get_fraction(arg);
		val = (val < 0) ? (val * -1.0) : (val);
		while (val >= 1.0 && precision > 0)
		{
			val /= 10.0;
			precision--;
		}
		ret = get_long_double(arg, precision);
	}
	return (ret);
}

char		*handle_float(long double arg, unsigned int precision)
{
	char	*temp;
	char	*ret;
	int		i;

	temp = get_norme_value(arg, precision);
	i = ft_strlen(temp) - 1;
	if (precision != 0)
	{
		while (temp[i] == '0')
			i--;
		if (temp[i] == '.')
			i--;
	}
	ret = ft_strsub(temp, 0, i + 1);
	ft_strdel(&temp);
	return (ret);
}
