# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 17:23:25 by linyao            #+#    #+#              #
#    Updated: 2024/11/25 16:54:19 by linyao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
INC			= ./inc/
LIB			= ./lib/
INC_HEADERS	= $(INC)minirt.h

FT			= $(LIB)libft/
FT_INC		= $(FT)/libft.h
FT_LNK		= -L$(FT) -lft
FT_LIB		= $(FT)libft.a

SRC_DIR		= src/
OBJ_DIR		= obj/

UNAME		= $(shell uname -s)
NUMPROC		= 8

ifeq ($(UNAME), Linux)
	NUMPROC = $(shell grep -c ^processor /proc/cpuinfo)
	LINKFLAGS  = -Lminilibx_linux -lmlx_Linux -L/usr/lib -Iminilibx_linux -lXext -lX11 -lm -lz
	MLX_DIR	= minilibx_linux
	MLX_TARGET = libmlx.a
	CFLAGS		= -I $(INC) -Iminilibx_linux -MMD -Wall -Werror -Wextra -O3
else ifeq ($(UNAME), Darwin)
	NUMPROC = $(shell sysctl -n hw.ncpu)
	LINKFLAGS	= -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = minilibx_macos
	MLX_TARGET = libmlx.a
	CFLAGS		= -I $(INC) -Iminilibx_macos -MMD -Wall -Werror -Wextra -O3
endif


RM			= rm -rf

DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

SRC_FILES	=	main.c \
				handle_errors.c \
				render_rt.c \
				ctrl_keys.c \
				init.c
				
							

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEP			= 	$(addsuffix .d, $(basename $(OBJ)))


all: $(NAME)

$(NAME): $(OBJ) $(FT_LIB)
		@$(MAKE) -C $(MLX_DIR)
		@echo "\n${MAGENTA}Minilibx compilation complete$(DEF_COLOR)\n"
#		@make -C ./minilibx_linux all
#		@cp ./minilibx_linux/libmlx.a .
		@$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) $(LINKFLAGS) -o $(NAME)
		@echo "$(GREEN)\nCreated ${NAME} ✓$(DEF_COLOR)\n"

$(FT_LIB):
		@$(MAKE) -C $(FT)

$(OBJ_DIR)%.o: %.c Makefile
			@mkdir -p $(dir $@)
			@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -c $< -o $@
#			@$(CC) $(CFLAGS) -I/usr/include -Iminilibx_linux -c $< -o $@

-include $(DEP)
#$(NAME):	$(OBJ)
#			@$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) $(LINKFLAGS) -o $(NAME)
#			@echo "$(GREEN)\nCreated ${NAME} ✓$(DEF_COLOR)\n"

#-include $(DEP)

bonus:		$(NAME)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make -C $(MLX_DIR) clean
			@make clean -C $(FT)
			@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f lib*.a
			@make fclean -C $(FT)
			@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"
#			@$(RM) -rf libmlx.dylib

re:			fclean all


.PHONY:		all clean fclean re norm
