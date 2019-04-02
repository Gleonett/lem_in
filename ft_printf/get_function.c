/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:18:25 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_get_output g_get_function_array[] = {
	&get_char,
	&get_string,
	&get_pointer,
	&get_int,
	&get_percent,
	NULL,
	&get_unsigned_int_oct,
	&get_unsigned_int,
	&get_unsigned_int_hex,
	&get_unsigned_int_hex_upper,
	&get_double,
	&get_long_double,
	&get_signed_char,
	NULL,
	&get_unsigned_char_oct,
	&get_unsigned_char,
	&get_unsigned_char_hex,
	&get_unsigned_char_hex_upper,
	&get_short,
	NULL,
	&get_unsigned_short_oct,
	&get_unsigned_short,
	&get_unsigned_short_hex,
	&get_unsigned_short_hex_upper,
	&get_double,
	&get_long,
	NULL,
	&get_unsigned_long_oct,
	&get_unsigned_long,
	&get_unsigned_long_hex,
	&get_unsigned_long_hex_upper,
	&get_long_long,
	NULL,
	&get_unsigned_long_long_oct,
	&get_unsigned_long_long,
	&get_unsigned_long_long_hex,
	&get_unsigned_long_long_hex_upper,
	&get_double_exp,
	&get_double_g,
	NULL,
	NULL,
	&get_long_double_exp,
	&get_long_double_g,
	&get_double_g_upper,
	NULL,
	&get_long_double_g_upper,
	&get_double_upper,
	NULL,
	&get_long_double_upper,
	&get_double_exp_upper,
	NULL,
	&get_long_double_exp_upper,
	&get_long_string,
	NULL,
	&get_long_char,
	NULL,
	&get_double_hex,
	&get_double_hex,
	&get_long_double_hex,
	&get_double_hex_upper,
	&get_double_hex_upper,
	&get_long_double_hex_upper,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&get_unsigned_int_bin,
	&get_unsigned_short_bin,
	&get_unsigned_char_bin,
	&get_unsigned_long_bin,
	&get_unsigned_long_long_bin,
	&get_date,
	&get_string_with_non_print
};

t_get_output	get_function(t_print *mod)
{
	int	size;

	size = sizeof(g_get_function_array) / sizeof(g_get_function_array[0]);
	if (size < mod->type)
		return (NULL);
	return (g_get_function_array[mod->type]);
}
