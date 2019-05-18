# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleonett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 19:31:05 by gleonett          #+#    #+#              #
#    Updated: 2019/05/18 18:06:55 by gleonett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem_in
LIB		= ft_printf
INC		= includes
LINC 	= ft_printf/libftprintf.a
FLAGS   =
#-Wall -Wextra -Werror
SRCS 	= main.c \
		bfs.c \
		collision.c \
		print_ants.c \
		valid_links.c \
		brute_force.c \
		sort_lvls.c \
		del_table.c \
		valid_room.c \
		distribution_ants.c \
		pow_p.c \
		reader.c \
		check_comment.c \
		init_room.c \
		prep_stream.c \
		sort_links.c \
		create_del_str_ants.c \
		find_num_ants.c \
		sharp_beginning.c \
		str_is_int.c
RAW_OBJ	= $(SRCS:.c=.o)
DOBJ	= obj

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
	@gcc $(FLAGS) $(LINC) $(OBJ) -o $(NAME)
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
	@gcc -I $(INC) -O $(LINC) $(SRCS) -o $(NAME)
	@time ./$(NAME)

$(DOBJ)/%.o : %.c
	@gcc $(FLAGS) -I$(INC) -O  -c $< -o $@