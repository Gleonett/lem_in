/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_double_g.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:30:55 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_long_double_g(long double arg, unsigned int precision)
{
	char *ret;

	if ((ret = get_const_double(arg)) != NULL)
		return (ret);
	if (is_exp(arg, precision))
		ret = handle_exp(arg, precision);
	else
		ret = handle_float(arg, precision);
	return (ret);
}
