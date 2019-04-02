/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:07:36 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 17:07:36 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_unsigned_char_bin(const void *arg)
{
	const unsigned char *value = arg;

	return (ulltobin(*value));
}

char	*get_unsigned_short_bin(const void *arg)
{
	const unsigned short *value = arg;

	return (ulltobin(*value));
}

char	*get_unsigned_int_bin(const void *arg)
{
	const unsigned int *value = arg;

	return (ulltobin(*value));
}

char	*get_unsigned_long_bin(const void *arg)
{
	const unsigned long *value = arg;

	return (ulltobin(*value));
}

char	*get_unsigned_long_long_bin(const void *arg)
{
	const unsigned long long *value = arg;

	return (ulltobin(*value));
}
