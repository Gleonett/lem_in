/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 12:53:21 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char *g_size = "hzjlL";
static const char *g_type = "{}cspi%douxXfegGFSCaAnDOUbkr";

static void	skip_size(const char *fmt, size_t *i, char *spec)
{
	int	k;
	int j;

	k = -1;
	j = 0;
	ft_bzero(spec, 20);
	while (g_size[j])
	{
		if (fmt[*i] == g_size[j])
		{
			while (fmt[*i] == g_size[j])
			{
				spec[++k] = g_size[j];
				*i += 1;
			}
			j = -1;
		}
		check_flags(g_mod, fmt, i);
		j++;
	}
}

void		check_type(const char *fmt, char ret[20], size_t *i)
{
	int		j;
	char	spec[20];

	skip_size(fmt, i, spec);
	j = -1;
	while (g_type[++j])
		if (fmt[*i] == g_type[j])
		{
			*i += 1;
			break ;
		}
	if (g_type[j] == '\0')
		return ;
	if (g_type[j] != '\0' && *spec != '\0')
		check_multiflag(ret, spec, (int)ft_strlen(spec), g_type[j]);
	if (*ret != '\0')
		ret[ft_strlen(ret)] = g_type[j];
	else
	{
		if (g_type[j] == '\0')
			return ;
		*ret = g_type[j];
	}
}
