/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:53:27 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_signed_char(const void *arg)
{
	const char *value = arg;

	return (ft_lltoa(*value));
}

char	*get_short(const void *arg)
{
	const short *value = arg;

	return (ft_lltoa(*value));
}

char	*get_int(const void *arg)
{
	const int *value = arg;

	return (ft_lltoa(*value));
}

char	*get_long(const void *arg)
{
	const long *value = arg;

	return (ft_lltoa(*value));
}

char	*get_long_long(const void *arg)
{
	const long long *value = arg;

	return (ft_lltoa(*value));
}
