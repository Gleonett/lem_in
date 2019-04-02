/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multiflag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 17:01:22 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char g_int_flags[][3] = {
	"hh",
	"h",
	"z",
	"j",
	"l",
	"ll",
};

static char g_char_flags[][3] = {
	"hh",
	"h",
	"l",
	"ll",
};

static char g_float_flags[][3] = {
	"l",
	"L"
};

static int g_len;

static int	compare(char sym1_1, char sym1_2, char sym2_1, char sym2_2)
{
	if (sym1_2 && sym2_2)
	{
		if (sym1_1 == sym2_1 && sym1_2 == sym2_2)
			return (1);
		else
			return (0);
	}
	else if (sym1_1 == sym2_1 && sym1_2 == 0)
		return (1);
	return (0);
}

static char	*check_multiflag_int(char *ret, char *flag, int size,
	char mass[][3])
{
	int	i;
	int	j;
	int	index;

	i = -1;
	index = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < g_len)
			if (compare(mass[j][0], mass[j][1], flag[i],
				((i + 1) < size) ? (flag[i + 1]) : (0)) == 1)
				if (j > index)
				{
					index = j;
					if (j == 0 || j == 5)
					{
						i++;
						break ;
					}
				}
	}
	if (index != -1)
		ft_strcpy(ret, mass[index]);
	return (ret);
}

static const char *g_type_int = "idouxXDOUb";
static const char *g_type_char = "csSCp";
static const char *g_type_float = "egfaEGFA";

void		check_multiflag(char *ret, char *flag, int size, char type)
{
	if (ft_strchr(g_type_int, type) != NULL)
	{
		g_len = sizeof(g_int_flags) / sizeof(g_int_flags[0]);
		check_multiflag_int(ret, flag, size, g_int_flags);
	}
	else if (ft_strchr(g_type_char, type) != NULL)
	{
		g_len = sizeof(g_char_flags) / sizeof(g_char_flags[0]);
		check_multiflag_int(ret, flag, size, g_char_flags);
	}
	else if (ft_strchr(g_type_float, type) != NULL)
	{
		g_len = sizeof(g_float_flags) / sizeof(g_float_flags[0]);
		check_multiflag_int(ret, flag, size, g_float_flags);
	}
}
