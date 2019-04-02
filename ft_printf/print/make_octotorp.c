/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_octotorp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:59:33 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	oct_part_1(char **output, char **new_output, size_t *len)
{
	*new_output = *output;
	while ((**new_output == ' ' || **new_output == '0') && *new_output)
		*new_output += 1;
	while (**new_output != ' ' && **new_output)
	{
		*new_output += 1;
		*len += 1;
	}
	if (*len < ft_strlen(*output))
	{
		if (**output == ' ')
			*(*new_output - *len - 1) = '0';
		else
		{
			ft_memmove(*output + 1, *(output), *len);
			**output = '0';
		}
		*new_output = *output;
	}
	else
		*new_output = ft_strcat(ft_strcpy(ft_strnew(
				ft_strlen(*output) + 1), "0"), *output);
}

static int	oct_part_2(char **output, char **new_output, int type, size_t len)
{
	if (len + 1 == (size_t)g_mod->width)
	{
		if (type == 9 || type == 17 || type == 23 || type == 30 ||
				type == 36 || (type >= 59 && type <= 61))
			*new_output = ft_strcat(ft_strcpy(ft_strnew(
					ft_strlen(*output) + 2), "0X"), *output);
		else
			*new_output = ft_strcat(ft_strcpy(ft_strnew(
					ft_strlen(*output) + 2), "0x"), *output);
		*new_output = ft_strcat(ft_strcpy(ft_strnew(len + 2), "0x"),
				*new_output);
		return (1);
	}
	else if (len > (size_t)g_mod->width)
	{
		if (type == 9 || type == 17 || type == 23 || type == 30 ||
				type == 36 || (type >= 59 && type <= 61))
			*new_output = ft_strcat(ft_strcpy(ft_strnew(
					ft_strlen(*output) + 2), "0X"), *output);
		else
			*new_output = ft_strcat(ft_strcpy(ft_strnew(
					ft_strlen(*output) + 2), "0x"), *output);
		return (1);
	}
	return (0);
}

static void	oct_part_3(char **output, char **new_output, int type, size_t *len)
{
	if (*new_output == *output && *len == (size_t)g_mod->width)
	{
		if ((*new_output)[*len - 1] == ' ' && (*new_output)[*len - 2] == ' ')
		{
			ft_memmove(*output + 2, *output, *len - 2);
			*new_output[0] = '0';
			if (type == 9 || type == 17 || type == 23 || type == 30 ||
			type == 36 || (type >= 59 && type <= 61))
				(*new_output)[1] = 'X';
			else
				(*new_output)[1] = 'x';
		}
	}
	else
	{
		*(*new_output - 2) = '0';
		if (type == 9 || type == 17 || type == 23 || type == 30 ||
				type == 36 || (type >= 59 && type <= 61))
			*(*new_output - 1) = 'X';
		else
			*(*new_output - 1) = 'x';
		*new_output = *output;
	}
}

static int	oct_part_4(char **output, char **new_output, int *k, size_t *len)
{
	*new_output = *output;
	if (IF_O_X(g_mod->type) && g_mod->precision != 0)
	{
		while ((**new_output == ' ' || **new_output == '0') && **new_output)
		{
			**new_output == '0' ? *k += 1 : 0;
			*new_output += 1;
		}
		*len = ft_strlen(*new_output);
		if (**new_output != '\0' && *k < 2)
		{
			if (oct_part_2(output, new_output, g_mod->type, *len) == 0)
				oct_part_3(output, new_output, g_mod->type, len);
		}
		else if (*k >= 2 && **new_output != '\0')
		{
			*new_output = ft_strchr(*output, '0');
			*(*new_output + 1) = 'x';
			*new_output = *output;
		}
		else
			*new_output = *output;
		return (1);
	}
	return (0);
}

int			make_octotorp(char **output)
{
	char	*new_output;
	int		type;
	int		k;
	size_t	len;

	type = g_mod->type;
	k = 0;
	len = 0;
	new_output = NULL;
	if (type == 6 || type == 14 || type == 20 || type == 27 || type == 33)
		oct_part_1(output, &new_output, &len);
	else if ((oct_part_4(output, &new_output, &k, &len)) == 0)
	{
		if (g_mod->precision == 0 && IF_OCT(type))
		{
			CH_NULL(new_output = ft_strcpy(ft_strnew(ft_strlen(*output) + 1),
				*output));
			new_output[ft_strlen(*output)] = '.';
		}
	}
	*output != new_output ? ft_strdel(output) : 0;
	return (((*output = new_output) == NULL) ? 0 : 1);
}
