/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 10:23:06 by rwalder-          #+#    #+#             */
/*   Updated: 2019/04/21 15:11:18 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H
# define CH_NULL(x) if((x) == NULL) exit(-1)
# define CH_ERROR(x) if((x) == 1) g_mod->error = 1;
# define P_NULL(x) if((x) == NULL) return (ft_strdup("(null)"));
# define MIN(x) (1LL << (sizeof(x) * 8 - 1))
# define DAY_TO_SEC(days) ((days) * 60 * 60 * 24)
# define LEAP_YEAR(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
# define EPOCH(sec) (((sec) >= 0) ? (1) : (-1))
# define IF_D_DD_1(x) ((x) == 10 || (x) == 11 || (x) == 24 || (x) == 37)
# define IF_D_DD_2(x) ((x) == 41 || (x) == 42 || (x) == 43 || (x) == 45)
# define IF_D_DD_3(x) ((x) == 38 || (x) == 46 || (x) == 49 || (x) == 51)
# define IF_D_DD(x) (IF_D_DD_1(x) || IF_D_DD_2(x) || IF_D_DD_3(x))
# define IF_OCT_1(x) ((x) == 10 || (x) == 11 || (x) == 24 || (x) == 37)
# define IF_OCT_2(x) ((x) == 38 || (x) == 39 || (x) == 40 || (x) == 41)
# define IF_OCT_3(x) ((x) == 42 || (x) == 43 || (x) == 45 || (x) == 46)
# define IF_OCT_4(x) ((x) == 48 || (x) == 49 || (x) == 51 || (x) == 52)
# define IF_OCT(x) (IF_OCT_1(x) || IF_OCT_2(x) || IF_OCT_3(x) || IF_OCT_4(x))
# define IF_O_X_1(x) (x == 8 || x == 9 || x == 16 || x == 17 || x == 22)
# define IF_O_X_2(x) (x == 23 || x == 29 || x == 30 || x == 36 || x == 35)
# define IF_O_X_3(x) ((x >= 56 && x <= 58) || (x >= 59 && x <= 61))
# define IF_O_X(x) (IF_O_X_1(x) || IF_O_X_2(x) || IF_O_X_3(x))
# define PUT_SEP(x) ({put_thousands_sep((x)); return (2);})
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define REBOOT "\e[0m"

# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>

typedef char		*(*t_get_output)();
typedef long		t_time_t;

typedef struct		s_print
{
	char			flag[6];
	int				type;
	int				num_arg;
	int				width;
	int				width_num_arg;
	int				precision;
	int				prec_num_arg;
	int				error;
	size_t			i;
	struct s_print	*next;
}					t_print;

int					g_output_symbols;
t_print				*g_start_list;
t_print				*g_mod;

int					ft_printf(const char *fmt, ...);
int					check_fmt(const char *fmt);
int					parser(va_list ap, va_list start);
int					print(const void *arg, double var_d, long double var_dd);
int					print_color(int j);
int					make_width(char **output);
void				flags_space_plus(char *output, size_t len);
int					make_precision(char **output);
int					make_octotorp(char **output);
int					number_of_argument(const char *fmt, size_t *i);
int					check_flags(t_print *mod, const char *fmt, size_t *i);
void				check_type(const char *fmt, char *ret, size_t *i);
void				choose_size_type(int j);
int					choose_color(const char *fmt, size_t *i, int *j);
void				clean_flags(t_print *mod);
t_print				*init_list(void);
void				del_list(int fail);
int					find_d_dd(void);
void				va_arg_num(va_list start, int num_arg, void **p);
void				va_arg_num_int(va_list start, int num_arg, int *value);
void				va_arg_num_d(va_list start, int num_arg, double *var_d);
void				va_arg_num_dd(va_list start, int num_arg,
						long double *var_dd);
void				va_arg_width(va_list start, va_list ap);
void				va_arg_precision(va_list start, va_list ap);
t_get_output		get_function(t_print *mod);
size_t				ft_strnchr(const char *s, char c);
void				ft_putstr_full(const char *str);
void				ft_putnstr_full(const char *str, size_t n);
char				*min_integer(size_t size);
char				*ft_lltoa(long long n);
char				*ft_ulltoa(unsigned long long n);
char				*ulltohex(unsigned long long value);
char				*ulltohex_upper(unsigned long long value);
char				*ulltooct(unsigned long long value);
char				*ulltobin(unsigned long long value);
long				sign_double(double val);
char				*wchar_to_str(int sym);
char				*get_const_double(double value);
char				*get_const_double_upper(double value);
long double			get_fraction(long double value);
void				ft_round(long double *int_part, long double *frac_part,
						unsigned int precision);
char				*get_fraction_str(long double frac_part,
						unsigned int precision,
					char **init_part_str);
char				*get_integer_str(long double int_part, long sign);
char				*check_overflow(char *val, int *exp);
char				*add_exp(char **val, int exp, unsigned int precesion);
char				*add_exp_upper(char **val, int exp, unsigned int precision);
int					is_exp(long double val, unsigned int precision);
char				*handle_exp(long double arg, unsigned int precision);
char				*handle_exp_upper(long double arg, unsigned int precision);
char				*handle_float(long double arg, unsigned int precision);
void				symtohex(unsigned long long c, char *hex,
						unsigned int size);
void				symtohex_upper(unsigned long long c, char *hex,
						unsigned int size);
long				get_mantissa(double val);
long				get_exponent(double val);
unsigned long		get_long_mantissa(long double val);
short				get_long_exponent(long double val);
char				*string_cut(char **val);
char				*add_comma(char **mantissa);
void				check_multiflag(char *ret, char *flag, int size, char type);

char				*get_char(const void *arg);
char				*get_percent(const void *arg);
char				*get_pointer(const void *arg);
char				*get_string(const void *arg);
char				*get_string_with_non_print(const void *arg);
char				*get_long_char(const void *arg);
char				*get_long_string(const void *arg, int precision);
char				*get_date(const void *arg);
char				*get_double(double arg, unsigned int precision);
char				*get_long_double(long double a, unsigned int precision);
char				*get_double_exp(double arg, unsigned int precision);
char				*get_long_double_exp(long double arg,
						unsigned int precision);
char				*get_double_g(double arg, unsigned int precision);
char				*get_long_double_g(long double arg, unsigned int precision);
char				*get_double_hex(double arg, int precision);
char				*get_double_upper(double arg, unsigned int precision);
char				*get_double_exp_upper(double arg, unsigned int precision);
char				*get_double_g_upper(double arg, unsigned int precision);
char				*get_long_double_upper(long double arg,
						unsigned int precision);
char				*get_long_double_exp_upper(long double arg,
						unsigned int precision);
char				*get_long_double_g_upper(long double arg,
						unsigned int precision);
char				*get_double_hex_upper(double arg, int precision);
char				*get_long_double_hex(long double arg, int precision);
char				*get_long_double_hex_upper(long double arg, int precision);
char				*get_signed_char(const void *arg);
char				*get_short(const void *arg);
char				*get_int(const void *arg);
char				*get_long(const void *arg);
char				*get_long_long(const void *arg);
char				*get_unsigned_char(const void *arg);
char				*get_unsigned_short(const void *arg);
char				*get_unsigned_int(const void *arg);
char				*get_unsigned_long(const void *arg);
char				*get_unsigned_long_long(const void *arg);
char				*get_unsigned_char_hex(const void *arg);
char				*get_unsigned_short_hex(const void *arg);
char				*get_unsigned_int_hex(const void *arg);
char				*get_unsigned_long_hex(const void *arg);
char				*get_unsigned_long_long_hex(const void *arg);
char				*get_unsigned_char_hex_upper(const void *arg);
char				*get_unsigned_short_hex_upper(const void *arg);
char				*get_unsigned_int_hex_upper(const void *arg);
char				*get_unsigned_long_hex_upper(const void *arg);
char				*get_unsigned_long_long_hex_upper(const void *arg);
char				*get_unsigned_char_oct(const void *arg);
char				*get_unsigned_short_oct(const void *arg);
char				*get_unsigned_int_oct(const void *arg);
char				*get_unsigned_long_oct(const void *arg);
char				*get_unsigned_long_long_oct(const void *arg);
char				*get_unsigned_char_bin(const void *arg);
char				*get_unsigned_short_bin(const void *arg);
char				*get_unsigned_int_bin(const void *arg);
char				*get_unsigned_long_bin(const void *arg);
char				*get_unsigned_long_long_bin(const void *arg);

#endif
