/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoli.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 11:52:40 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/09 11:53:38 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoli(const char *str)
{
	int			znak;
	long int	res;

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
	return (znak * res);
}
