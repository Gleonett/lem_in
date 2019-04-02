/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hex_upper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:02:21 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 17:02:21 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_unsigned_char_hex_upper(const void *arg)
{
	const unsigned char *value = arg;

	return (ulltohex_upper(*value));
}

char	*get_unsigned_short_hex_upper(const void *arg)
{
	const unsigned short *value = arg;

	return (ulltohex_upper(*value));
}

char	*get_unsigned_int_hex_upper(const void *arg)
{
	const unsigned int *value = arg;

	return (ulltohex_upper(*value));
}

char	*get_unsigned_long_hex_upper(const void *arg)
{
	const unsigned long *value = arg;

	return (ulltohex_upper(*value));
}

char	*get_unsigned_long_long_hex_upper(const void *arg)
{
	const unsigned long long *value = arg;

	return (ulltohex_upper(*value));
}
