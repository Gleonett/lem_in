/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:54:05 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/19 18:54:07 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	zero_way(int way, short ret_fill, short **ways, int len)
{
	int k;

	k = way + 1;
	while (--k > -1 && k >= ret_fill)
		ways[k][len] = 0;
	return (-1);
}
