/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:54:39 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/02 18:54:43 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	iter(int xyz[], short flag)
{
	if (flag == 1)
	{
		xyz[0] += 1;
		xyz[1] -= 1;
	}
	else if (flag == 2)
		xyz[2] += 1;
	else if (flag == 3)
		xyz[0] += 1;
	else if (flag == 4)
		xyz[1] -= 1;
	else if (flag == 5)
		xyz[1] += 1;
	else if (flag == 6)
		xyz[0] -= 1;
	else if (flag == 7)
	{
		xyz[0] -= 1;
		xyz[1] += 1;
	}
	if (flag != 2)
		xyz[2] = 0;
}

void	bruteforce(int xyz[], short **mtrx, short path[])
{
	if (xyz[0] == xyz[3] && xyz[1] == xyz[4]))
		path += new path;
	if (x+1, y-1)
	{
		iter(xyz, 1);
		return (bruteforce(xyz, mtrx, path));
	}
	if (z+1)
	{
		iter(xyz, 2);
		return (bruteforce(xyz, mtrx, path));
	}
	if (x+1)
	{
		iter(xyz, 3);
		return (bruteforce(xyz, mtrx, path));
	}
	if (y-1)
	{
		iter(xyz, 4);
		return (bruteforce(xyz, mtrx, path));
	}
	if (y+1 && y+1 not in path)
	{
		iter(xyz, 5);
		return (bruteforce(xyz, mtrx, path));
	}
	if (x-1 && x-1 not in path)
	{
		iter(xyz, 6);
		return (bruteforce(xyz, mtrx, path));
	}
	if (x-1 && x-1 not in path && y+1 && y+1 not in path)
	{
		iter(xyz, 7);
		return (bruteforce(xyz, mtrx, path));
	}
	else
		return (TUPIK_SUKA);
}