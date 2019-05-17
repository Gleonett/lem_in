/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lvls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 12:37:54 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/12 12:35:52 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	sort_insert(short **tab, int k, int d, int len)
{
	short	*buf;
	int		j;

	if (tab[k][len] > tab[k + d][len])
	{
		buf = tab[k + d];
		j = k;
		while (j >= 0 && buf[len] < tab[j][len])
		{
			tab[j + d] = tab[j];
			j -= d;
		}
		tab[j + d] = buf;
	}
}

int				shells_sort(short **tab, int size, int d, int len)
{
	int	i;
	int	k;

	i = 0;
	while (i < d)
	{
		k = i;
		while (k + d <= size)
		{
			sort_insert(tab, k, d, len);
			k += d;
		}
		i++;
	}
	if (d < 1)
		return (0);
	else
		shells_sort(tab, size, d / 2, len);
	return (0);
}
