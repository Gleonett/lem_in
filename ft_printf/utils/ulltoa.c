/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulltoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:14:25 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_intlen(unsigned long long n)
{
	size_t				ret;
	unsigned long long	num;

	ret = 0;
	num = n;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		ret++;
		num = num / 10;
	}
	return (ret);
}

char			*ft_ulltoa(unsigned long long n)
{
	long				len;
	char				*ret;
	unsigned long long	num;

	len = ft_intlen(n);
	CH_NULL(ret = (char*)malloc(sizeof(char) * (len + 1)));
	ret[len--] = '\0';
	num = n;
	while (len >= 0)
	{
		ret[len] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (ret);
}
