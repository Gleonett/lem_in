/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_exp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:15:16 by rwalder-          #+#    #+#             */
/*   Updated: 2019/01/30 14:17:02 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_overflow(char *val, int *exp)
{
	int		sign;
	int		i;
	size_t	len;

	sign = 0;
	i = 0;
	while (val[i] != '.')
	{
		if (val[i] == '-')
			sign = 1;
		i++;
	}
	if ((i - sign) >= 2)
	{
		val[i] = val[i - 1];
		val[i - 1] = '.';
		len = ft_strlen(val);
		val[len - 1] = 0;
		*exp = *exp + 1;
	}
	return (val);
}

char	*add_exp(char **val, int exp, unsigned int precesion)
{
	char	*exp_str;
	char	*temp;
	char	*ret;

	if (precesion != 0)
		check_overflow(*val, &exp);
	temp = ft_lltoa((exp >= 0) ? (exp) : (exp * -1));
	if (ft_strlen(temp) == 1)
	{
		ret = temp;
		temp = ft_strjoin("0", ret);
		ft_strdel(&ret);
	}
	if (exp >= 0)
		exp_str = ft_strjoin("e+", temp);
	else
		exp_str = ft_strjoin("e-", temp);
	ft_strdel(&temp);
	ret = ft_strjoin(*val, exp_str);
	ft_strdel(val);
	*val = ret;
	return (ret);
}

char	*add_exp_upper(char **val, int exp, unsigned int precision)
{
	char	*exp_str;
	char	*temp;
	char	*ret;

	if (precision != 0)
		check_overflow(*val, &exp);
	temp = ft_lltoa((exp >= 0) ? (exp) : (exp * -1));
	if (ft_strlen(temp) == 1)
	{
		ret = temp;
		temp = ft_strjoin("0", ret);
		ft_strdel(&ret);
	}
	if (exp >= 0)
		exp_str = ft_strjoin("E+", temp);
	else
		exp_str = ft_strjoin("E-", temp);
	ft_strdel(&temp);
	ret = ft_strjoin(*val, exp_str);
	ft_strdel(val);
	*val = ret;
	return (ret);
}
