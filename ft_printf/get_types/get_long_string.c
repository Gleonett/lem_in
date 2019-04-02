/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:40:02 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_long_string(const void *arg, int precision)
{
	int			i;
	const int	**wstr = (const int **)arg;
	char		*ret;
	char		*join;
	char		*temp;

	if (*wstr == NULL)
		return (ft_strdup("(null)"));
	i = 0;
	ret = ft_strdup("");
	while ((*wstr)[i] != 0 && precision != 0)
	{
		temp = wchar_to_str((*wstr)[i++]);
		join = ft_strjoin(ret, temp);
		ft_strdel(&temp);
		ft_strdel(&ret);
		ret = join;
		if (precision != -1 && ((int)ft_strlen(ret) >= (precision - 1)))
			break ;
	}
	return (ret);
}
