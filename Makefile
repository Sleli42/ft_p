# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/01 19:09:41 by lubaujar          #+#    #+#              #
#    Updated: 2015/09/21 20:23:26 by lubaujar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server
RM = rm -rf
FLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -I./include/ -I./libft/include/

SRC_CLIENT = client.c \
				c_init.c \
				c_tools.c \
				c_error.c
SRC_SERVER = server.c \
				s_init.c \
				s_error.c \
				s_builtins.c \
				s_exec.c \
				s_tools.c \
				debug.c

OBJ_C = $(SRC_CLIENT:.c=.o)
OBJ_S = $(SRC_SERVER:.c=.o)

	SRCDIR_C	= ./srcs_client/
	SRCDIR_S	= ./srcs_server/
	OBJDIR_C	= ./objs_client/
	OBJDIR_S	= ./objs_server/
	INCDIR	= ./include/
	SRCS_C	= $(addprefix $(SRCDIR_C), $(SRC_CLIENT))
	SRCS_S	= $(addprefix $(SRCDIR_S), $(SRC_SERVER))
	OBJS_C	= $(addprefix $(OBJDIR_C), $(OBJ_C))
	OBJS_S	= $(addprefix $(OBJDIR_S), $(OBJ_S))
	INCS	= $(addprefix $(INCDIR), $(INC))

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJS_C) $(INCS)
	@gcc $(FLAGS) -o $@ $^ -L./libft/ -lft

$(NAME_S): $(OBJS_S) $(INCS)
	@gcc $(FLAGS) -o $@ $^ -L./libft/ -lft
	@echo "\\033[1;34m\tPlease wait ...\\033[0;39m"
	@echo "\\033[1;34m\t\texec ./ftp\\033[0;39m"

$(OBJS_C): $(SRCS_C)
	@make -C libft/
	@gcc $(FLAGS) -c $(SRCS_C) $(LDFLAGS)
	@mkdir -p $(OBJDIR_C)
	@mv $(OBJ_C) $(OBJDIR_C)

$(OBJS_S): $(SRCS_S)
	@make -C libft/
	@gcc $(FLAGS) -c $(SRCS_S) $(LDFLAGS)
	@echo "\\033[1;34mPlease wait ...\\033[0;39m"
	@mkdir -p $(OBJDIR_S)
	@mv $(OBJ_S) $(OBJDIR_S)

clean:
	@echo "\nRM *.o.. \t      \033[35mDELETE!\033[0m"
	@$(RM) $(OBJS_C)
	@$(RM) $(OBJS_S)
	@$(RM) *.o

fclean: clean
	@make fclean -C libft/
	@echo "RM ./ftp..\t\t \033[35mDELETE!\033[0m"
	@$(RM) $(NAME_C) $(NAME_S)

re: fclean all

.PHONY: all clean fclean re
