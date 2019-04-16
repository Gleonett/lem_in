# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/28 16:05:16 by gleonett          #+#    #+#              #
#    Updated: 2019/04/14 11:42:12 by gleonett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LNAME = ../libft
SRCS = *.c get_types/*.c utils/*.c va_functions/*.c print/*.c \
        check_fmt/*.c
INC = ../includes
LINC = ../libft/libft.a
OBJ = ../libft/*.o *.o
FLAGS = -Wall -Wextra -Werror -Ofast

all: $(NAME)

$(NAME):
	@make -C $(LNAME)
	@gcc   -I $(INC) -c $(SRCS) $(FLAGS)
	@ar rc $(NAME) $(OBJ)

clean:
	@make clean -C $(LNAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LNAME)
	@rm -f $(NAME)

re: fclean all
