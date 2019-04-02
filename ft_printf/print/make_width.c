/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:41:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/04 21:42:11 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	flag_0(char **new_output, char **output, size_t len)
{
	int f;

	f = 0;
	if ((g_mod->precision <= 0) &&
		(g_mod->type == 3 || g_mod->type == 0 || g_mod->type != 54 ||
		(g_mod->type >= 4 && g_mod->type <= 9) ||
		(g_mod->type >= 12 && g_mod->type <= 23) ||
		(g_mod->type >= 25 && g_mod->type <= 36)))
	{
		ft_memset(*new_output, '0', (size_t)g_mod->width);
		if (g_mod->type == 2)
		{
			ft_strncpy(*new_output, *output, 2);
			ft_strcpy((*new_output + g_mod->width - len + 2), *output + 2);
		}
		else
			ft_memcpy((*new_output + g_mod->width - len), *output, len);
		f++;
	}
	return (f);
}

static int	flag_minus(char *new_output, char **output, size_t *len)
{
	ft_memset(new_output, ' ', (size_t)g_mod->width);
	if (g_mod->type == 0 || g_mod->type == 54)
		*len = 1;
	ft_memcpy(new_output, *output, *len);
	return (1);
}

static int	flags_width(char **new_output, char **output, int i)
{
	int		f;
	size_t	len;

	f = 0;
	if ((len = ft_strlen(*output)) >= (size_t)g_mod->width)
		return (0);
	while (g_mod->flag[++i])
		if (g_mod->flag[i] == '-')
		{
			f = flag_minus(*new_output, output, &len);
		}
		else if (g_mod->flag[i] == '0')
			f = flag_0(new_output, output, len);
	if (f == 0)
	{
		if (g_mod->type == 2)
			ft_memcpy(*new_output, *output, len);
		ft_memset(*new_output, ' ', (size_t)g_mod->width);
		if (g_mod->type == 0 || g_mod->type == 54)
			len = 1;
		ft_memcpy((*new_output + g_mod->width - len), *output, len);
	}
	return (1);
}

int			make_width(char **output)
{
	int		i;
	char	*new_output;
	t_print *mod;

	mod = g_mod;
	if (ft_strlen(*output) >= (size_t)mod->width)
		return (0);
	if ((new_output = ft_strnew((size_t)mod->width)) == NULL)
		return (0);
	i = -1;
	flags_width(&new_output, output, i);
	if (mod->type >= 3 && mod->type != 4 && mod->type != 6 && mod->type != 8 &&
			mod->type != 9 && mod->type != 14 && mod->type != 16 &&
			mod->type != 17 && mod->type != 20 && mod->type != 22 &&
			mod->type != 23 && mod->type != 27 && mod->type != 29 &&
			mod->type != 30 && mod->type != 33 && mod->type != 35 &&
			mod->type != 36 && mod->type <= 52)
		flags_space_plus(new_output, ft_strlen(*output));
	ft_strdel(output);
	*output = new_output;
	return (1);
}
