# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleonett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 19:31:05 by gleonett          #+#    #+#              #
#    Updated: 2019/04/16 09:52:15 by gleonett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem_in
LIB		= ft_printf
INC		= includes
LINC 	= ft_printf/libftprintf.a
SRCS 	= bfs.c           collision.c     init_room.c     pow_p.c         sort_links.c    valid_room.c \
		prep_stream.c	check_comment.c del_table.c     main.c          reader.c        valid_links.c \
		brute_force.c
RAW_OBJ		= $(SRCS:.c=.o)
DOBJ	= obj
FLAGS	= ""
# -Wall -Wextra -Werror

OBJ = $(addprefix $(DOBJ)/,$(RAW_OBJ))

# COLORS
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
REB			= \033[0m
UNDERLINE	= \033[4m

run:
	@time ./$(NAME)

all: $(DOBJ) $(LINC) $(NAME)

$(DOBJ):
	@mkdir $(DOBJ)

$(LINC):
	@make -C $(LIB)

$(NAME): $(OBJ)
	@gcc $(LINC) $(OBJ) -o $(NAME) $(FLAGS)
	@echo "	-Building $(GREEN)LEM_IN$(REB) is completed, $(UNDERLINE)My lord$(REB)!"

$(DOBJ)/%.o : %.c
	@gcc $(FLAGS) -I $(INC) -c $< -o $@

clean:
	@make clean -C $(LIB)
	@rm -rf $(DOBJ)
	@echo "	-The stables are cleaned, $(UNDERLINE)My lord$(REB)!"

fclean: clean
	@make fclean -C $(LIB)
	@rm -f $(NAME)
	@echo "	-And pigsies too!"

re: fclean all

ez: $(OBJ)
	@gcc -I $(INC) $(LINC) $(SRCS) -o $(NAME) $(FLAGS)
	@time ./$(NAME)

$(DOBJ)/%.o : %.c
	@gcc $(FLAGS) -I$(INC) -c $< -o $@