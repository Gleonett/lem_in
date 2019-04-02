/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_oct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:05:33 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 17:05:33 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_unsigned_char_oct(const void *arg)
{
	const unsigned char *value = arg;

	return (ulltooct(*value));
}

char	*get_unsigned_short_oct(const void *arg)
{
	const unsigned short *value = arg;

	return (ulltooct(*value));
}

char	*get_unsigned_int_oct(const void *arg)
{
	const unsigned int *value = arg;

	return (ulltooct(*value));
}

char	*get_unsigned_long_oct(const void *arg)
{
	const unsigned long *value = arg;

	return (ulltooct(*value));
}

char	*get_unsigned_long_long_oct(const void *arg)
{
	const unsigned long long *value = arg;

	return (ulltooct(*value));
}
