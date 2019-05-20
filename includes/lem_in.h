/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:52:52 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/12 20:39:17 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H

# define PATH "/Users/gleonett/Desktop/lem-in/maps/"
# define MAP PATH "map228"

# define NUM_ROOMS 8313
# define NUM_SMBLS 1500000
# define NUM_LINKS 100
# define POW 127
# define SIZE_POW 10
# define START (th[NUM_ROOMS - 2])
# define FINISH (th[NUM_ROOMS - 1])
# define Q_ADD 0
# define Q_GET 1

# define MOD(x) (x >= 0 ? x : x * -1)
# define IF_1_RET(x, y, z) if (x == 1) ({ft_memdel((void **)y); return (z);})
# define IF_FALSE(x) if (x == 0) ({return (-1);})
# define IF_EQ_BRK(x, y) if (x == y) ({break ;})
# define CGO_1 (i->links[vars.j]->p_x >= i->p_x + BIG_MAP)
# define CGO_2 ((i->links[vars.j]->p_x > 1 || i->p_x == 0))
# define CAN_GO_ON (i->links[vars.j]->flag != 1  && CGO_1 && CGO_2)
# define BIG_MAP (g_ways.diff > 150 ? 1 : -1)
# define SAME_LVL2 ((g_vars.baned_lvls)[(g_vars.ways)[i][g_vars.len]])
# define SAME_LVL if (SAME_LVL2 == 1) ({i++; continue ;})
# define END_BRT2 (len > (g_vars.start)->num_links || g_vars.num_ends > 5000)
# define END_BRT if (END_BRT2) ({return (0);})

/*
**exit (255) - ошибка выделения памяти
*/

# include "ft_printf.h"

typedef	struct		s_tbhash
{
	char			*room;
	struct s_tbhash	**links;
	struct s_tbhash	*next;
	struct s_tbhash	*queue_prev;
	short			place_mtrx;
	short			p_x;
	short			p_y;
	short			p_z;
	int				lvl;
	short			flag;
	short			num_links;
}					t_tbhash;

typedef struct		s_mtrx
{
	short			**ways;
	short			**final_ways;
	short			*baned_lvls;
	int				num_a_r[2];
	short			num_ways;
	short			total_links;
}					t_mtrx;

typedef struct		s_d_a
{
	int				num_ants_in_turn;
	struct s_d_a	*dist_ants;
}					t_d_a;

typedef struct		s_th_pow_p
{
	t_tbhash		**th;
	size_t			*pow_p;
	char			*buf;
}					t_th_pow_p;

typedef struct		s_printing
{
	int				last_ant;
	int				shift;
	short			max_num_ways;
}					t_printing;

typedef struct		s_for_dfs
{
	short			**ways;
	int				way;
	int				num_rooms;
	short			diff;
}					t_for_dfs;

typedef struct		s_in_dfs
{
	short			j;
	short			num_links;
	short			ret;
	short			flag;
	short			ret_fill;
}					t_in_dfs;

typedef struct		s_for_brtfrc
{
	short			**final_ways;
	short			**ways;
	short			**ret_ways;
	short			*baned_lvls;
	t_mtrx			*mtrx;
	t_tbhash		*start;
	int				len;
	short			total_ways;
	int				const_buf;
	int				max_ways;
	int				num_ends;
}					t_for_brtfrc;

typedef struct		s_in_brtfrc
{
	short			*line;
	short			j;
	int				buf;
	short			k;
	short			flag;
}					t_in_brtfrc;

/*
**		MAIN
*/
void				power_p(size_t pow_p[]);
size_t				power_p_more(size_t max_p, size_t i);
/*
**		READER
*/
int					reader(t_th_pow_p *th_p, t_mtrx *mtrx);
int					skip_spaces(const char *str, int *i);
int					str_is_int(const char *str);
int					valid_room(char const *s, t_tbhash **th, size_t pow_p[],
						int f);
int					collision(t_tbhash **th, int res, t_tbhash *room);
int					check_comment(char **line, t_th_pow_p *th_p, char *buf,
						int fd);
int					valid_links(t_tbhash **th, size_t pow_p[], const char *s);
void				bufcat_and_write(char **s1, const char *s2, int flag);
t_tbhash			*init_room(void);
/*
**		BFS
*/
int					bfs(t_tbhash **th);
void				sort_links(t_tbhash **th, t_tbhash *room);
void				shortcpy(short *dst, short *src, size_t len);
/*
**		DFS
*/
short				prep_dfs(t_tbhash **th, t_mtrx *mtrx, int num_a_r[2]);
int					zero_way(int way, short ret_fill, short **ways, int len);
/*
**		BRUTE FORCE
*/
void				prep_brute_force(t_tbhash **th, t_mtrx *ways);
int					shells_sort(short **tab, int size, int d, int len);
int					count_turns(short **final_ways, t_mtrx *ways, short *k);
/*
**		DISTRIBUTION ANTS
*/
void				distribution_ants(t_tbhash **th, t_mtrx *mtrx);
char				**create_del_str_ants(char ***ants, int num_ants,
						int get_del);
int					sharp_beginning(t_d_a *dist_ants, char ***final_ways,
						char **str_ants, t_printing *prnt);
void				cpy(char *room, char *ant);
void				print_ants(char ***final_ways, t_mtrx *mtrx);
int					*find_num_ants(int ants, short **final_ways, short num_ways,
						int j);
void				add_start_d_a(t_d_a **start_list, short num);
/*
**		FREE
*/
void				del_tables(t_tbhash ***th);
void				del_d_a_list(t_d_a **start);
void				del_room(t_tbhash **room);

#endif
