/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:52:52 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/02 12:03:19 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H

//# define MAP "/Users/gleonett/Desktop/lem_in/maps/map228"
# define MAP "/Users/gleonett/Desktop/lem_in/maps/map3"
# define NUM_ROOMS 9975
# define NUM_LINKS 20
# define SIZE_MTRX 1000
# define POW 127
# define SIZE_POW 10
# define START (th[NUM_ROOMS - 2])
# define FINISH (th[NUM_ROOMS - 1])
# define Q_ADD 0
# define Q_GET 1
# define X p_x - 1
# define Y p_y - 1

# define MOD(x) (x >= 0 ? x : x * -1)
# define IF_TRUE_RET(x, y, z) if (x == 1) ({ft_memdel((void **)y); return (z);})
# define IF_FALSE(x) if (x == 0) return (-1);

/*
**exit (3) - ошибка выделения памяти
*/

# include "ft_printf.h"

typedef struct		s_mtrx
{
	short 			mtrx[SIZE_MTRX][SIZE_MTRX];
	int				num_a_r[2];
}					t_mtrx;

typedef	struct		s_tbhash
{
	char			*room;
	short			place_mtrx;
	short			p_x;
	short			p_y;
	short			p_z;
	short			num_links;
	short			true_way;
	struct s_tbhash	**links;
	struct s_tbhash	*next;
	struct s_tbhash	*way;
	struct s_tbhash	*queue_prev;
	int				x;
	int				y;
}					t_tbhash;

/*
** функции под вопросом
*/
void				sort_links(t_tbhash **th, t_tbhash *room, t_tbhash *bf);

int					reader(t_tbhash **th, size_t *pow_p, t_mtrx *mtrx);
int					str_is_int(const char *str);
int					valid_room(char const *s, t_tbhash **th, size_t pow_p[],
						int f);
int					collision(t_tbhash **th, int res, t_tbhash *room);
int					check_comment(char **line, t_tbhash **th, size_t pow_p[],
						int fd);
int					valid_links(t_tbhash **th, size_t pow_p[], const char *s);
t_tbhash			*init_room(void);
t_tbhash			****init_field(int n_r, int n_x_y[]);
void				del_tables(t_tbhash ***th, t_tbhash *****field, int n_r,
						int n_x_y[]);
void				del_room(t_tbhash **room);
void				power_p(size_t pow_p[]);
size_t				power_p_more(size_t max_p, size_t i);
int					skip_spaces(const char *str, int *i);

int					bfs(t_tbhash **th, t_tbhash *****field, int n_x_y[2],
						t_mtrx	mtrx);
#endif