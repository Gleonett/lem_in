/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 09:59:50 by gleonett          #+#    #+#             */
/*   Updated: 2019/02/08 15:00:28 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *stolp;
	t_list *ydali;

	if (!alst || !*alst || !del)
		return ;
	stolp = *alst;
	while (stolp->next != NULL)
	{
		del(stolp->content, stolp->content_size);
		ydali = stolp;
		stolp = stolp->next;
		free(ydali);
	}
	del(stolp->content, stolp->content_size);
	free(stolp);
	*alst = NULL;
}
