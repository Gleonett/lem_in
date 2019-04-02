/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:55:49 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			number_of_argument(const char *fmt, size_t *i)
{
	size_t	j;
	int		ret;

	j = *i;
	while (fmt[j] >= '0' && fmt[j] <= '9')
		j++;
	if (fmt[j] != '$')
		return (0);
	ret = ft_atoi(fmt + *i);
	*i = j + 1;
	return (ret);
}

int g_k = -1;

static int	clean_flgs_if(char true_flgs[6], const char flgs[7], int *j, int *i)
{
	if (g_mod->flag[*j] == '0' && (ft_strchr(true_flgs, '-') !=
		NULL || (g_mod->precision != -1 && g_mod->type != 0 &&
		g_mod->type != 54 && g_mod->type != 1 && g_mod->type != 52
		&& g_mod->type != 4)))
		return (0);
	if (g_mod->flag[*j] == ' ' &&
		(ft_strchr(true_flgs, '+') != NULL))
		return (0);
	if (g_mod->flag[*j] == '#')
		g_mod->flag[*j] = '#';
	true_flgs[++g_k] = flgs[*i];
	return (1);
}

void		clean_flags(t_print *g_mod)
{
	const char	flgs[7] = "-+ 0#'";
	char		true_flgs[6];
	int			i;
	int			j;

	i = -1;
	g_k = -1;
	ft_bzero(true_flgs, 6);
	while (flgs[++i] != '\0')
	{
		j = -1;
		while (g_mod->flag[++j] != '\0')
			if (g_mod->flag[j] == flgs[i])
			{
				if ((clean_flgs_if(true_flgs, flgs, &j, &i)) == 0)
					break ;
			}
	}
	ft_bzero(g_mod->flag, 6);
	ft_strcpy(g_mod->flag, true_flgs);
}

static void	skip_double(const char *fmt, size_t *i, int *k)
{
	while (g_mod->flag[*k] != '\0')
	{
		if (fmt[*i] == g_mod->flag[*k] && fmt[*i] != '%')
		{
			*i += 1;
			*k = 0;
		}
		else
			*k += 1;
	}
	if (fmt[*i] >= '1' && fmt[*i] <= '9')
		g_mod->num_arg = number_of_argument(fmt, i);
}

int			check_flags(t_print *g_mod, const char *fmt, size_t *i)
{
	const char	flgs[10] = "-+ 0#'~";
	int			j;
	int			k;

	k = 0;
	while (k < 7)
	{
		j = 0;
		k = 0;
		skip_double(fmt, i, &k);
		while (fmt[*i] != flgs[j] && flgs[j])
			j++;
		if (flgs[j] != '\0')
		{
			g_mod->flag[k] = flgs[j];
			*i += 1;
		}
		else
		{
			g_mod->flag[k] = '\0';
			break ;
		}
	}
	return (0);
}
