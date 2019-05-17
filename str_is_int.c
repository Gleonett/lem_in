/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:38:28 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/17 16:38:29 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			skip_spaces(const char *str, int *i)
{
	while (str[*i] && (str[*i] == '\t' || str[*i] == ' '))
		*i += 1;
	return (str[*i] == '\0' ? 1 : 0);
}

int			str_is_int(const char *str)
{
	int i;
	int j;

	i = 0;
	if (skip_spaces(str, &i) == 1)
		return (-1);
	j = i;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i - j > 12 || ((str[j] == '+' || str[j] == '-') && (i - j == 1)))
		return (0);
	else if (str[j] == '-')
		return (i * -1);
	return (i);
}
