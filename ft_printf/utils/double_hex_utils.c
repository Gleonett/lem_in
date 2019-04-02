/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_hex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:51:48 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long			get_mantissa(double val)
{
	long ret;
	long mask;

	mask = 0xFFF;
	mask <<= 52;
	mask = ~mask;
	ret = *(long*)&val;
	return (ret & mask);
}

long			get_exponent(double val)
{
	long ret;
	long sign;

	sign = 1;
	sign <<= 63;
	ret = *(long*)&val;
	ret &= ~sign;
	ret >>= 52;
	return (ret);
}

unsigned long	get_long_mantissa(long double val)
{
	return (*(unsigned long *)&val);
}

short			get_long_exponent(long double val)
{
	short			ret;
	long			sign;
	unsigned long	*p;

	p = (unsigned long *)&val;
	sign = 1;
	sign <<= 15;
	ret = (short)*(p + 1);
	ret &= ~sign;
	return (ret);
}

char			*string_cut(char **val)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(*val);
	i = len - 1;
	if ((*val)[len - 1] != '.' && (*val)[len - 1] != '0')
		return (*val);
	while (i >= 0 && ((*val)[i] == '0' || (*val)[i] == '.'))
		i--;
	ret = ft_strsub(*val, 0, i + 1);
	return (ret);
}
