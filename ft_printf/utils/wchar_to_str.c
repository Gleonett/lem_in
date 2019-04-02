/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 09:20:52 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 09:28:47 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*wchar_to_str(int sym)
{
	int		mask;
	char	*ret;
	int		size;

	if (sym < 0xFF && (size = 1))
		mask = sym;
	else if (sym < 0xFFF && (size = 2))
		mask = 0xC080 | (sym & 0x3F) | ((sym & 0x7C0) << 2);
	else if (sym < 0xFFFF && (size = 3))
		mask = 0xE08080 | (sym & 0x3F) | ((sym & 0xFC0) << 2)
			| ((sym & 0xF000) << 4);
	else if (sym < 0xFFFFF && (size = 4))
		mask = 0xF0808080 | (sym & 0x3F) | ((sym & 0xFC0) << 2)
			| ((sym & 0x1F000) << 4) | ((sym & 0x3C0000) << 6);
	ret = ft_strnew(size--);
	while (size >= 0)
	{
		ret[size--] = (char)mask;
		mask >>= 8;
	}
	return (ret);
}
