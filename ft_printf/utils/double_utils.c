/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:02:09 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 18:07:33 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_round(long double *int_part, long double *frac_part,
	unsigned int precision)
{
	int			i;
	long double	div;

	if (precision == 0)
	{
		if (*frac_part == 0.5)
			if ((long)(*int_part) % 2 == 1)
				*int_part = *int_part + 1;
		if (*frac_part > 0.5)
			*int_part = *int_part + 1;
	}
	else
	{
		i = -1;
		div = 0.5;
		while (++i < (int)precision)
			div /= 10;
		*frac_part = *frac_part + div;
		if (*frac_part >= 1)
		{
			*frac_part = *frac_part - 1;
			*int_part = *int_part + 1;
		}
	}
}

long double	get_fraction(long double value)
{
	long double		ret;
	unsigned long	a;

	ret = value;
	if (ret < 0)
		ret *= -1.0;
	a = (unsigned long)-1;
	if (ret <= a)
	{
		a = (unsigned long)ret;
		ret = ret - a;
	}
	else
	{
		while (ret > (double)a)
			ret = ret / 10;
		a = (unsigned long)ret;
		ret = ret - a;
	}
	return (ret);
}

char		*get_fraction_str(long double frac_part, unsigned int precision,
	char **init_part_str)
{
	long	temp;
	int		i;
	char	*ret;
	char	*frac_part_str;

	i = 0;
	CH_NULL(frac_part_str = ft_strnew(precision + 1));
	frac_part_str[i++] = '.';
	while (i < (int)(precision + 1))
	{
		frac_part *= 10;
		temp = (long)(frac_part);
		frac_part_str[i] = '0' + temp;
		frac_part -= temp;
		i++;
	}
	ret = ft_strjoin(*init_part_str, frac_part_str);
	ft_strdel(init_part_str);
	*init_part_str = ret;
	return (ret);
}

static int	long_int_part(long double *int_part)
{
	int i;

	i = 0;
	while (*int_part >= 1.0)
	{
		*int_part /= 10;
		i++;
	}
	return (i);
}

char		*get_integer_str(long double int_part, long sign)
{
	int			i;
	char		*ret;
	long double	temp;
	int			count;

	temp = ((int_part < 0) ? (int_part * -1.0) : (int_part)) + 0.5;
	if (int_part == 0.0)
	{
		CH_NULL(ret = ft_strdup((sign == 0) ? "0" : "-0"));
		return (ret);
	}
	i = long_int_part(&temp);
	i = (sign == 0) ? (i - 1) : (i);
	CH_NULL(ret = ft_strnew(i));
	ret[++i] = 0;
	ret[0] = '-';
	count = (int_part < 0) ? 1 : 0;
	while (--i >= (int_part < 0) ? 1 : 0)
	{
		temp *= 10;
		ret[count++] = (int)temp + '0';
		temp -= (int)temp;
	}
	return (ret);
}
