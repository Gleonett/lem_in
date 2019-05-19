/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:24:28 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/20 16:42:04 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static void	del_section(t_sections **sect)
{
	t_pointers			*pnt;
	t_pointers			*back_pnt;

	pnt = (*sect)->list;
	while (pnt != NULL)
	{
		back_pnt = pnt;
		pnt = pnt->next;
		ft_memdel(&(back_pnt->pointer));
		ft_memdel((void **)&back_pnt);
	}
	ft_memdel((void **)&((*sect)->section_name));
	ft_memdel((void **)sect);
}

static void	del_all(t_sections **start)
{
	t_sections	*front;
	t_sections	*back;

	front = *start;
	while (front != NULL)
	{
		back = front;
		front = front->next_section;
		del_section(&back);
	}
	*start = NULL;
}

static void	find_del_section(t_sections **start, char *section)
{
	t_sections	*front;
	t_sections	*back;

	front = *start;
	back = NULL;
	while (front != NULL && ft_strcmp(front->section_name, section) != 0)
	{
		back = front;
		front = front->next_section;
	}
	if (front == NULL)
		return ;
	back != NULL ? back->next_section = front->next_section : 0;
	back == NULL ? *start = front->next_section : 0;
	del_section(&front);
}

static void	add_section(t_sections **start, void *pointer, char *section)
{
	t_sections	*front;
	t_pointers	*point;

	front = *start;
	while (front != NULL && ft_strcmp(front->section_name, section))
		front = front->next_section;
	if (front == NULL)
	{
		front = *start != NULL ? *start : NULL;
		if ((*start = (t_sections *)malloc(sizeof(t_sections))) == NULL)
			exit(-1);
		if (((*start)->section_name = ft_strdup(section)) == NULL)
			exit(-1);
		(*start)->next_section = front;
		front = *start;
		front->list = NULL;
	}
	point = front->list;
	if ((front->list = (t_pointers *)malloc(sizeof(t_pointers))) == NULL)
		exit(-1);
	front->list->pointer = pointer;
	front->list->next = point;
}

void		*gc(void *pointer, char *section, int del_add)
{
	static t_sections	*start;

	if (start == NULL && del_add == GC_DEL)
		return (NULL);
	if (del_add == GC_ADD)
		add_section(&start, pointer, section);
	else if (del_add == GC_DEL && ft_strcmp(section, GC_ALL) == 0)
		del_all(&start);
	else if (del_add == GC_DEL)
		find_del_section(&start, section);
	return (pointer);
}
