/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulltooct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:00:10 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	symtooct(unsigned long long c, char *hex, unsigned int size)
{
	int value;
	int count;

	count = size - 1;
	while (count >= 0)
		hex[count--] = '0';
	count = size - 1;
	while (c > 0)
	{
		value = c;
		c = c / 8;
		value = value - c * 8;
		hex[count--] = '0' + value;
	}
}

char		*ulltooct(unsigned long long value)
{
	char		*ret;
	char		*temp;
	const int	size = 45;
	int			i;

	CH_NULL(temp = ft_strnew(size));
	symtooct(value, temp, size);
	i = 0;
	while (temp[i] == '0' && i < size - 1)
		i++;
	ret = ft_strdup(temp + i);
	ft_strdel(&temp);
	return (ret);
}
