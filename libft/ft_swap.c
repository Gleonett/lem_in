/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:13:06 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/23 09:55:44 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void **a, void **b)
{
	void *c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_memswap(void *a, void *b, size_t size)
{
	char c[size];

	ft_memcpy(c, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, c, size);
}
