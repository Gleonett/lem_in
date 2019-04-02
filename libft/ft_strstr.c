/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:15:05 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 15:00:29 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;

	i = -1;
	if (haystack == NULL || needle == NULL)
		return (NULL);
	if (*haystack == '\0' && *needle == '\0')
		return ((char *)haystack);
	else if (*haystack != '\0' && *needle == '\0')
		return ((char *)haystack);
	else if (*haystack == '\0' && *needle != '\0')
		return (0);
	while (haystack[++i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] || needle[j] == '\0')
			if (needle[j++] == '\0' || needle[j] == '\0')
				return ((char *)haystack + i);
	}
	return (0);
}
