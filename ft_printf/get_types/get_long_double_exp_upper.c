/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_double_exp_upper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 16:47:42 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_long_double_exp_upper(long double arg, unsigned int precision)
{
	int		exp;
	char	*ret;
	int		sign;

	if ((ret = get_const_double_upper(arg)) != NULL)
		return (ret);
	exp = 0;
	sign = (arg >= 0.0) ? (1) : (-1);
	arg *= sign;
	if (arg >= 10.0)
		while (arg >= 10.0)
		{
			arg /= 10.0;
			exp++;
		}
	else if (arg != 0.0)
		while (arg < 1)
		{
			arg *= 10.0;
			exp--;
		}
	arg *= sign;
	ret = get_long_double_upper(arg, precision);
	add_exp_upper(&ret, exp, precision);
	return (ret);
}
