/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:36:43 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/22 19:26:30 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_quick_sort(int *tab, int a, int b)
{
	int i;
	int j;
	int f;

	i = a;
	j = b;
	f = 0;
	if (a >= b)
		return (0);
	while (++i <= j)
		if (tab[i] >= tab[a])
		{
			while (tab[j] >= tab[a] && j > i)
				j--;
			if (j != i)
				ft_swap_int(&tab[i], &tab[j]);
			else
				f++;
		}
	if (f == 0)
		ft_swap_int(&tab[a], &tab[j]);
	ft_quick_sort(tab, a, j - 1);
	ft_quick_sort(tab, i - 1, b);
	return (0);
}
