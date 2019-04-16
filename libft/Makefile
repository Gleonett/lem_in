# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/29 11:47:02 by gleonett          #+#    #+#              #
#    Updated: 2019/04/14 11:42:12 by gleonett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = *.c
INC = ../includes
OBJ = *.o
FLAGS = -Wall -Wextra -Werror -Ofast

all: $(NAME)

$(NAME):
	@gcc -I $(INC) $(FLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
