/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:00:00 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 17:00:00 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_unsigned_char(const void *arg)
{
	const unsigned char *value = arg;

	return (ft_ulltoa(*value));
}

char	*get_unsigned_short(const void *arg)
{
	const unsigned short *value = arg;

	return (ft_ulltoa(*value));
}

char	*get_unsigned_int(const void *arg)
{
	const unsigned int *value = arg;

	return (ft_ulltoa(*value));
}

char	*get_unsigned_long(const void *arg)
{
	const unsigned long *value = arg;

	return (ft_ulltoa(*value));
}

char	*get_unsigned_long_long(const void *arg)
{
	const unsigned long long *value = arg;

	return (ft_ulltoa(*value));
}
