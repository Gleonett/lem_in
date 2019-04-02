/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:08:30 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 15:00:28 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					znak;
	unsigned long long	res;

	znak = 1;
	res = 0;
	while ((*str == '\n') || (*str == '\t') || (*str == '\v') ||
		(*str == ' ') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
		*str++ == '-' ? znak = -1 : 1;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + ((*str++) - 48);
	if (res > 9223372036854775807)
	{
		if (znak > 0)
			return (-1);
		else
			return (0);
	}
	return (znak * (int)res);
}
