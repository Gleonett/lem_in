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

//# define MAP "/Users/gleonett/Desktop/lem_in/maps/map3"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/lol_map"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/map228"
# define MAP "/Users/gleonett/Desktop/lem_in/maps/rand_map"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/rand_map_2"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/1"
//# define MAP "/Users/gleonett/Desktop/lem_in/maps/jest'"
//# define NUM_ROOMS 9975
# define NUM_ROOMS 3333
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
# define IF_FALSE(x) if (x == 0) return (-1);
# define IF_EQ_BRK(x, y) if (x == y) ({break ;})
# define BIG_MAP (g_ways.diff > 150 ? 1 : -1)

/*
**exit (255) - ошибка выделения памяти
*/

# include "ft_printf.h"

typedef	struct		s_tbhash
{
	char			*room;
	short			place_mtrx;
	short			p_x;
	short			p_y;
	short			p_z;
	int				lvl;
	short			flag;
	short			num_links;
	struct s_tbhash	*next;
	struct s_tbhash	*queue_prev;
//	int				x;
//	int				y;
	struct s_tbhash	**links;
}					t_tbhash;

typedef struct		s_mtrx
{
	short			**ways;
	short			**final_ways;
	short			num_ways;
	short			*num_lvls;
	short			*baned_lvls;
	int				num_a_r[2];
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
}					t_th_pow_p;

typedef struct		s_printing
{
	int				last_ant;
	int				shift;
	short			max_num_ways;
}					t_printing;

typedef struct		s_for_dfs
{
	int				way;
	int				num_rooms;
	short			**ways;
	short			diff;
}					t_for_dfs;

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
void				bufcat_and_write(char *s1, const char *s2, int flag);
t_tbhash			*init_room(void);
/*
**		BFS
*/
int					bfs(t_tbhash **th);
void				sort_links(t_tbhash **th, t_tbhash *room);
/*
**		DFS
*/
short				**prep_dfs(t_tbhash **th, t_mtrx *mtrx, int num_a_r[2]);
/*
**		BRUTE FORCE
*/
void				prep_brute_force(t_tbhash **th, t_mtrx *ways);
int					shells_sort(short **tab, int size, int d, int len);
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
