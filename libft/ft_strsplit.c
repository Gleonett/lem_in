/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:29:03 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 15:00:29 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit_2(char **arr, char const *s, char c, int i)
{
	int		k;
	size_t	f;
	size_t	nach;

	k = -1;
	while (s[i])
	{
		f = 0;
		nach = i;
		while (s[i] != c && s[i])
		{
			f++;
			i++;
		}
		if (f > 0)
		{
			arr[++k] = ft_strnew(f);
			if (arr[k] == 0)
				return (0);
			arr[k] = ft_strncpy(arr[k], s + nach, f);
		}
		(s[i] != '\0') ? i++ : 0;
	}
	arr[++k] = 0;
	return (arr);
}

char	**ft_strsplit(char const *s, char c)
{
	int		i;
	int		k;
	size_t	f;
	char	**arr;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	while (s[i++] != '\0')
	{
		f = 0;
		while (s[i] != c && s[i++])
			f++;
		if (f != 0)
			k++;
	}
	arr = (char **)malloc(sizeof(char *) * (k));
	if (!arr)
		return (0);
	i = 0;
	arr = ft_strsplit_2(arr, s, c, i);
	return (arr == 0 ? 0 : arr);
}
