/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:58:11 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 15:00:28 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fillitoa(char *arr, int size, int k, int n)
{
	while (size > 0)
	{
		size /= 10;
		k++;
	}
	arr = ft_strnew(k);
	if (!arr)
		return (0);
	while (n > 0)
	{
		arr[--k] = (n % 10) + 48;
		n /= 10;
	}
	return (arr);
}

char		*ft_itoa(int n)
{
	int		size;
	int		k;
	char	*arr;
	char	znak;

	arr = 0;
	k = 0;
	znak = 'J';
	if (n == -2147483648)
		return (ft_strcpy(ft_strnew(11), "-2147483648"));
	if (n == 0)
		return (ft_strcpy(ft_strnew(1), "0"));
	if (n < 0)
	{
		znak = '-';
		k++;
		n = n * -1;
	}
	size = n;
	if ((arr = ft_fillitoa(arr, size, k, n)) == 0)
		return (0);
	if (znak == '-')
		arr[0] = '-';
	return (arr);
}
