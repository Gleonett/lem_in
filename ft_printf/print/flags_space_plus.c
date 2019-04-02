/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_space_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:29:23 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/04 20:06:23 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	exceptions_width(char *output, int *i, int *j, size_t len)
{
	if ((len > (size_t)g_mod->width && *output != '-') &&
			(g_mod->type != 6 && g_mod->type != 7 && g_mod->type != 14 &&
			g_mod->type != 15 && g_mod->type != 20 && g_mod->type != 21 &&
			g_mod->type != 27 && g_mod->type != 28 && g_mod->type != 33 &&
			g_mod->type != 34))
		g_mod->flag[*i] == ' ' ? ft_putstr_full(" ") : ft_putstr_full("+");
	if (len < (size_t)g_mod->width)
	{
		*j = 0;
		while (output[*j] != '\0' && (output[*j] == '0' ||
				output[*j] == ' '))
			*j += 1;
		if (output[*j] == '-')
		{
			if (*output == '0')
			{
				output[*j] = output[*j - 1];
				*output = '-';
			}
		}
		return (1);
	}
	return (0);
}

static void	exceptions_2(char *output, int *j, int *i)
{
	if (*output == '0' && ft_strnchr(output, '0') > 0 &&
			ft_strchr(g_mod->flag, '0') != NULL)
	{
		if (g_mod->flag[*i] == '+')
			*output = '+';
		else
			*output = ' ';
	}
	else if (*output == ' ' && ft_strchr(output, '-') == NULL)
	{
		*j = 0;
		while (output[*j] == ' ')
			*j += 1;
		g_mod->flag[*i] == '+' ? (output[*j - 1] = '+') :
				(*(output) = ' ');
	}
}

static void	exceptions(char *output, int *i, int *j, size_t len)
{
	if (((exceptions_width(output, i, j, len)) == 1) &&
			(g_mod->type == 3 || g_mod->type == 0 || g_mod->type != 54 ||
					(g_mod->type >= 4 && g_mod->type <= 9) ||
					(g_mod->type >= 12 && g_mod->type <= 23) ||
					(g_mod->type >= 25 && g_mod->type <= 36)) &&
			(g_mod->type != 7 && g_mod->type != 15 && g_mod->type != 21
					&& g_mod->type != 28 && g_mod->type != 34))
	{
		if (*output == '0' && ft_strnchr(output, ' ') > 0)
		{
			ft_memmove(output + 1, output,
					ft_strlen(output) - ft_strnchr(output, ' '));
			if (g_mod->flag[*i] == '+')
				*output = '+';
			else
				*output = ' ';
		}
		else
			exceptions_2(output, j, i);
	}
}

void		flags_space_plus(char *output, size_t len)
{
	int i;
	int j;

	if (g_mod->type < 3)
		return ;
	i = -1;
	while (g_mod->flag[++i])
		if (g_mod->flag[i] == ' ' || g_mod->flag[i] == '+' ||
			ft_strchr(output, '-') != NULL)
		{
			if (*output != ' ' && *output != '0' && *output != '-' &&
					len < (size_t)g_mod->width)
			{
				ft_memmove(output + 1, output, len);
				if (g_mod->flag[i] == '+')
					(output[0] = '+');
				else
					(output[0] = ' ');
			}
			exceptions(output, &i, &j, len);
			break ;
		}
}
