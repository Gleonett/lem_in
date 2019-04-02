/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:15:12 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/20 13:15:12 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_memalloc(size_t size, char *section)
{
	void *obl;

	obl = malloc(size);
	if (obl == NULL)
		return (NULL);
	ft_bzero(obl, size);
	gc(obl, section, GC_ADD);
	return (obl);
}

void	*gc_malloc(size_t size, char *section)
{
	void *obl;

	obl = malloc(size);
	if (obl == NULL)
		return (NULL);
	gc(obl, section, GC_ADD);
	return (obl);
}
