/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_size_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:07:02 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/13 16:27:27 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	choose_size_type_2(int j)
{
	if (j == 53 || j == 91)
		g_mod->type = 52;
	else if (j == 55 || j == 90)
		g_mod->type = 54;
	else if (j == 63)
		g_mod->type = 25;
	else if (j == 64)
		g_mod->type = 27;
	else if (j == 65)
		g_mod->type = 28;
	else if (j == 66 || j == 68 || j == 80 || j == 82 ||
			j == 88 || j == 100 || j == 102 || j == 105)
		g_mod->type = 34;
	else if (j == 67 || j == 69 || j == 83 || j == 78 || j == 86 || j == 79
			|| j == 89 || j == 103 || j == 104)
		g_mod->type = 31;
	else if (j == 70 || j == 96)
		g_mod->type = 35;
	else if (j == 81 || j == 84 || j == 85 || j == 87 ||
			j == 92 || j == 94 || j == 95 || j == 98)
		g_mod->type = 33;
	else if (j == 93 || j == 97)
		g_mod->type = 36;
	else
		g_mod->type = j;
}

void		choose_size_type(int j)
{
	if (j == 5)
		g_mod->type = 3;
	else if (j == 99)
		g_mod->type = 2;
	else if (j == 13)
		g_mod->type = 12;
	else if (j == 19)
		g_mod->type = 18;
	else if (j == 26)
		g_mod->type = 25;
	else if (j == 32 || j == 101)
		g_mod->type = 31;
	else if (j == 39)
		g_mod->type = 37;
	else if (j == 40)
		g_mod->type = 38;
	else if (j == 44)
		g_mod->type = 43;
	else if (j == 47)
		g_mod->type = 46;
	else if (j == 50)
		g_mod->type = 49;
	else
		choose_size_type_2(j);
}

static const char g_color[][8] = {
	"BLACK ", "RED ", "GREEN ", "YELLOW ", "BLUE ", "PURPLE ",
	"CYAN ", "WHITE ", "MEOW ", "BOGDAN ", "GOOSE ", "GG ", "}", ""
};

int			choose_color(const char *fmt, size_t *i, int *j)
{
	int		k;
	size_t	size;

	k = 0;
	size = 1;
	if (fmt[*i - 1] == '}')
		*i -= 1;
	while (g_color[k][size] != '\0')
	{
		if (ft_strncmp(fmt + *i, g_color[k], size) == 0)
			size++;
		else
		{
			++k;
			size = 1;
		}
	}
	*j += 106 + k;
	g_mod->type = *j;
	*i += size;
	return (0);
}
