/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_del_str_ants.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:10:03 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/14 18:10:06 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**create_del_str_ants(char ***ants, int num_ants, int get_del)
{
	int i;

	i = -1;
	if (get_del == 0)
	{
		CH_NULL(*ants = (char **)malloc(sizeof(char *) * (num_ants + 2)));
		while (++i <= num_ants)
		{
			(*ants)[i] = ft_itoa(i);
		}
		return (*ants);
	}
	while (++i <= num_ants)
		free((*ants)[i]);
	free(*ants);
	*ants = NULL;
	return (NULL);
}
