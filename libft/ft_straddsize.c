/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:37:38 by gleonett          #+#    #+#             */
/*   Updated: 2018/12/03 09:52:14 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddsize(char *s, size_t n)
{
	char	*new;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size <= n)
		return (s);
	new = ft_strnew(ft_strlen(s));
	if (!new)
		return (NULL);
	new = ft_strncpy(new, s, size);
	free(s);
	s = NULL;
	return (new);
}
