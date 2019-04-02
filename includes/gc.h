/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:28:41 by gleonett          #+#    #+#             */
/*   Updated: 2019/03/20 16:39:43 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H
# define GC_ADD 1
# define GC_DEL 0
# define GC_ALL "all"

# include "libft.h"

typedef	struct			s_pointers
{
	void				*pointer;
	struct s_pointers	*next;
}						t_pointers;

typedef	struct			s_sections
{
	char				*section_name;
	struct s_sections	*next_section;
	struct s_pointers	*list;
}						t_sections;

void					*gc(void *pointer, char *section, int del_add);
void					*gc_memalloc(size_t size, char *section);
void					*gc_malloc(size_t size, char *section);

#endif
