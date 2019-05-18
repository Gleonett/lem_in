/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:45:58 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/22 14:18:13 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	power_p(size_t pow_p[])
{
	const size_t	p = POW;
	int				i;

	pow_p[0] = 1;
	i = 0;
	while (++i < SIZE_POW)
		pow_p[i] = pow_p[i - 1] * p;
}

size_t	power_p_more(size_t max_p, size_t i)
{
	const size_t	p = POW;
	long long int	power;

	power = i - SIZE_POW;
	while (--power > -1)
		max_p *= p;
	return (max_p);
}
