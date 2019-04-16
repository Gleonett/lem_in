/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:52:52 by gleonett          #+#    #+#             */
/*   Updated: 2019/04/16 17:56:17 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H

//# define MAP "/Users/gleonett/Desktop/lem_in/maps/lol_map"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/map228"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/rand_map"
# define MAP "/Users/gleonett/Desktop/lem_in/maps/map3"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/jest'"
# define NUM_ROOMS 9975
# define NUM_LINKS 20
# define SIZE_MTRX 1000
# define POW 127
# define SIZE_POW 10
# define START (th[NUM_ROOMS - 2])
# define FINISH (th[NUM_ROOMS - 1])
# define Q_ADD 0
# define Q_GET 1

# define MOD(x) (x >= 0 ? x : x * -1)
# define IF_TRUE_RET(x, y, z) if (x == 1) ({ft_memdel((void **)y); return (z);})
# define IF_FALSE(x) if (x == 0) return (-1);

/*
**exit (3) - ошибка выделения памяти
*/

# include "ft_printf.h"

typedef	struct		s_tbhash
{
	char			*room;
	int 			num_ant;

	short			place_mtrx;
	short			p_x;
	short			p_y;
	short			p_z;
	short			flag;
	short			num_links;
	short			true_way;
	struct s_tbhash	**links;
	struct s_tbhash	*next;
	struct s_tbhash	*way;
	struct s_tbhash	*queue_prev;
	int				x;
	int				y;
}					t_tbhash;

typedef struct		s_mtrx
{
	short 			**ways;
	short 			**final_ways;
	short 			*num_lvls;
	short 			*baned_lvls;
	int				num_a_r[2];
}					t_mtrx;

/*
** функции под вопросом
*/
void				print_mtrx(short **mtrx, int num);
void				print_bigraph(t_tbhash ***bigr, int num_a_r[2]);
void				sort_links(t_tbhash **th, t_tbhash *room);

short				**prep_dfs(t_tbhash **th, t_mtrx *mtrx, int num_a_r[2]);
void		 		prep_brute_force(t_tbhash **th, t_mtrx *ways);

int					reader(t_tbhash **th, size_t *pow_p, t_mtrx *mtrx);
int					str_is_int(const char *str);
int					valid_room(char const *s, t_tbhash **th, size_t pow_p[],
						int f);
int					collision(t_tbhash **th, int res, t_tbhash *room);
int					check_comment(char **line, t_tbhash **th, size_t pow_p[],
						int fd);
int					valid_links(t_tbhash **th, size_t pow_p[], const char *s,
						short **mtrx);
t_tbhash			*init_room(void);
short				**init_mtrx(int num_rooms);
void				del_tables(t_tbhash ***th, int n_r, int n_x_y[]);
void				del_mtrx(t_mtrx *mtrx);
void				del_room(t_tbhash **room);
void				power_p(size_t pow_p[]);
size_t				power_p_more(size_t max_p, size_t i);
int					skip_spaces(const char *str, int *i);

int					bfs(t_tbhash **th, int n_x_y[2], t_mtrx	mtrx);
#endif
