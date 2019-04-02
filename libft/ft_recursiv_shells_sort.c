/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursiv_shells_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:04:53 by gleonett          #+#    #+#             */
/*   Updated: 2018/12/03 09:17:07 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	sort_vstavkami(int *tab, int k, int d)
{
	int	buf;
	int	j;

	if (tab[k] > tab[k + d])
	{
		buf = tab[k + d];
		j = k;
		while (j >= 0 && buf < tab[j])
		{
			tab[j + d] = tab[j];
			j -= d;
		}
		tab[j + d] = buf;
	}
}

int				ft_recursiv_shells_sort(int *tab, int size, int d)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < d)
	{
		k = i;
		while (k + d <= size)
		{
			sort_vstavkami(tab, k, d);
			k += d;
		}
		i++;
	}
	if (d < 1)
		return (0);
	else
		ft_recursiv_shells_sort(tab, size, d / 2);
	return (0);
}
