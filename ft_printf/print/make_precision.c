/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_precision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:12:29 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/05 12:09:43 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	prec_exceptions(char *output, char **new_output)
{
	if (g_mod->precision < 0)
		return (1);
	if (g_mod->type == 0 || g_mod->type == 54)
	{
		g_mod->precision = -1;
		return (1);
	}
	if (g_mod->type == 1 || g_mod->type == 52)
	{
		if ((*new_output = ft_strnew((size_t)g_mod->precision)) == 0)
			return (1);
		ft_strncpy(*new_output, output, (size_t)g_mod->precision);
		return (2);
	}
	return (0);
}

static int	prec_part_1(char **output, char **new_output, size_t *len)
{
	*len = ft_strlen(*output);
	if (**output == '0' && g_mod->precision == 0)
		if (ft_strnchr(*output, '0') == 1 && ft_strchr(*output, 'x') == NULL)
		{
			if (g_mod->width <= 0)
				ft_strchr(*output, '0')[0] = '\0';
			else
				ft_strchr(*output, '0')[0] = ' ';
		}
	if ((size_t)g_mod->precision < *len)
	{
		if ((g_mod->type == 2) && g_mod->precision == 0)
		{
			if (ft_strnchr(*output, '0') == 2)
				ft_strchr(*output, 'x')[1] = '\0';
		}
		return (1);
	}
	if (ft_strchr(*output, '-') != NULL)
		g_mod->precision += 1;
	if ((*new_output = ft_strnew((size_t)g_mod->precision)) == 0)
		exit(-1);
	return (0);
}

static void	prec_part_2(char **output, char **new_output, char **minus,
		size_t len)
{
	if ((g_mod->type == 8 || g_mod->type == 16 || g_mod->type == 22 ||
			g_mod->type == 29 || g_mod->type == 35) && **output != '0')
	{
		if (!(ft_strchr(g_mod->flag, '#') == NULL && g_mod->precision > 1))
		{
			*ft_strchr(g_mod->flag, '#') = '\0';
			ft_putstr_full("0x");
		}
		ft_strcpy(*new_output + (g_mod->precision - len), *output);
	}
	else if (g_mod->type == 2)
	{
		*minus = ft_strnew((size_t)g_mod->precision + 2);
		ft_strcpy(*minus, "0x");
		ft_strcat(*minus, *new_output);
		ft_strcpy((*minus + g_mod->precision + 2 - len + 2), *output + 2);
		ft_strdel(new_output);
		*new_output = *minus;
	}
	else
		ft_strcpy(*new_output + (g_mod->precision - len), *output);
}

int			make_precision(char **output)
{
	char	*new_output;
	size_t	len;
	char	*minus;
	int		buf;

	if ((buf = prec_exceptions(*output, &new_output)) == 1)
		return (0);
	else if (buf != 2)
	{
		if ((buf = prec_part_1(output, &new_output, &len)) == 1)
			return (0);
		else if (buf != 2)
		{
			ft_memset(new_output, '0', (size_t)g_mod->precision);
			prec_part_2(output, &new_output, &minus, len);
			if ((minus = ft_strchr(new_output, '-')) != NULL)
			{
				*minus = '0';
				new_output[0] = '-';
			}
		}
	}
	ft_strdel(output);
	*output = new_output;
	return (1);
}
