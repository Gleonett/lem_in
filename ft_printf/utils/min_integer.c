/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_integer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:59:38 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*min_integer(size_t size)
{
	if (size == 16)
		return (ft_strdup("−170141183460469231731687303715884105728"));
	if (size == 8)
		return (ft_strdup("-9223372036854775808"));
	if (size == 4)
		return (ft_strdup("−2147483648"));
	if (size == 2)
		return (ft_strdup("−32768"));
	if (size == 1)
		return (ft_strdup("−127"));
	return (NULL);
}
