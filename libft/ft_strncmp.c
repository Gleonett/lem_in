/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:20:35 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/19 13:17:56 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t            i;

	i = 0;
	if (n == 0 && s2[i] == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == 0)
			return (0);
		i++;
	}
	return (0);
}
//
//int	ft_strncmp(const char *s1, const char *s2, size_t n)
//{
//	size_t i;
//
//	i = 0;
//	if (n == 0)
//		return (0);
//	while (s1[i] == s2[i] && s1[i] && i < n)
//		i++;
//	if (i != n && (unsigned char)(s1)[i] > 127)
//		return ((unsigned char)(s1[i] - s2[i]));
//	return (0);
//}
