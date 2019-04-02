/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 12:38:51 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_pointer(const void *arg)
{
	char				*hex;
	char				*ret;
	int					i;
	const int			size = 32;
	const unsigned long	**val = (const unsigned long **)arg;

	if (*val == NULL)
		return (ft_strdup("0x0"));
	hex = ft_strnew(size);
	symtohex((unsigned long)(*val), hex, size);
	i = 0;
	while (hex[i] == '0')
		i++;
	ret = ft_strnew(2 + size - i);
	ft_strcat(ret, "0x");
	ft_strcat(ret, hex + i);
	ft_strdel(&hex);
	return (ret);
}
