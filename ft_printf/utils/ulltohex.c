/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulltohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:39:49 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ulltohex(unsigned long long value)
{
	char		*ret;
	char		*temp;
	const int	size = 32;
	int			i;

	CH_NULL(temp = ft_strnew(size));
	symtohex(value, temp, size);
	i = 0;
	while (temp[i] == '0' && i < size - 1)
		i++;
	ret = ft_strdup(temp + i);
	ft_strdel(&temp);
	return (ret);
}
