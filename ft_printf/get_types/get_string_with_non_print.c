/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_with_non_printable.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 09:17:33 by rwalder-          #+#    #+#             */
/*   Updated: 2019/02/08 08:56:54 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*add_char_non_print(char **str, unsigned char sym)
{
	char	*ret;
	char	*code_sym;
	int		len;

	ret = ft_itoa(sym);
	len = ft_strlen(ret);
	if (len == 3)
		code_sym = ft_strjoin("\\", ret);
	else if (len == 2)
		code_sym = ft_strjoin("\\0", ret);
	else if (len == 1)
		code_sym = ft_strjoin("\\00", ret);
	ft_strdel(&ret);
	ret = ft_strjoin(*str, code_sym);
	ft_strdel(str);
	*str = ret;
	return (ret);
}

static char	*put_sym(char **ret, const char *s, int start, int len)
{
	char *sub;
	char *temp;

	sub = ft_strsub(s, start, len);
	temp = ft_strjoin(*ret, sub);
	ft_strdel(ret);
	*ret = temp;
	return (*ret);
}

char		*get_string_with_non_print(const void *arg)
{
	const char	**s = (const char**)arg;
	int			i;
	char		*ret;
	int			len;
	int			start;

	P_NULL(*s);
	i = -1;
	len = 0;
	ret = ft_strnew(1);
	start = 0;
	while ((*s)[++i] != '\0')
	{
		if (((*s)[i] < ' ' || (*s)[i] > '~') && len != 0)
			ret = put_sym(&ret, *s, start, len);
		if ((*s)[i] < ' ' || (*s)[i] > '~')
		{
			ret = add_char_non_print(&ret, (unsigned char)(*s)[i]);
			len = 0;
			start = i + 1;
		}
		else
			len++;
	}
	return (put_sym(&ret, *s, start, len));
}
