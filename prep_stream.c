/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:38:57 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/04 19:32:36 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_tbhash	**init_moves(t_tbhash *finish, int n_a_r[], short num_links)
{
	t_tbhash	**moves;
	int			i;
	int			buf;
	int			ants;
	int			ants_in_way;
	short		max_pow;

	i = 0;
	max_pow = (short)(num_links < n_a_r[0] ? num_links : n_a_r[0]);
	buf = finish->num_links;
	while (++i < finish->num_links)
		finish->links[i]->p_x > buf ? buf = finish->links[i]->p_x : 0;
	buf = buf + n_a_r[0];
	CH_NULL(moves = (t_tbhash **)ft_memalloc(sizeof(t_tbhash *) * buf));
	moves[buf - 1] = NULL;
	i = -1;
	ants = n_a_r[0];
	ants_in_way = num_links;
	while (ants > 0)
	{
		ants -= max_pow;
		CH_NULL(moves[i] = (t_tbhash *)malloc(sizeof(t_tbhash) *
													  (ants_in_way + 1)));
		ants_in_way = ants_in_way + max_pow;
	}
	while (++i < buf)
	{
		CH_NULL(moves[i] = (t_tbhash *)malloc(sizeof(t_tbhash) *
				(ants_in_way + 1)));
	}
	return (moves);
}

static void		del_moves(t_tbhash ***moves)
{
	int i;

	i = -1;
	while((*moves)[++i] != NULL)
		ft_memdel((void **)(*moves) + i);
	ft_memdel((void **)moves);
}

//[] = {x, y, z, num_ant};

int			prep_stream(t_tbhash ****field, t_tbhash *start, t_tbhash *finish,
						t_mtrx mtrx)
{
	t_tbhash **moves;

	moves = init_moves(finish, mtrx.num_a_r,
			start->num_links < finish->num_links ?
			start->num_links : finish->num_links);
	stream(field, mtrx, moves);
	del_moves(&moves);
	return (0);
}