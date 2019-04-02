/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 09:59:31 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 15:00:29 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	size_t	j;
	char	*str;

	if (!s)
		return (0);
	i = 0;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
		i++;
	j = i;
	while (s[i])
		i++;
	while ((s[--i] == ' ' || s[i] == '\t' || s[i] == '\n') && i != -1)
		;
	if (i == -1)
		str = ft_strnew(0);
	else
		str = ft_strnew((size_t)i - j + 1);
	if (!str)
		return (0);
	if (i == -1)
		return (str);
	return (ft_strncpy(str, s + j, (size_t)i - j + 1));
}
