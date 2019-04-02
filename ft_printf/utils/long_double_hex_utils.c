/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_double_hex_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:46:30 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_comma(char **mantissa)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	len = ft_strlen(*mantissa);
	ret = ft_strnew(len + 1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (j == 1)
		{
			ret[j] = '.';
			j++;
			continue ;
		}
		ret[j] = (*mantissa)[i];
		j++;
		i++;
	}
	ft_strdel(mantissa);
	return (ret);
}
