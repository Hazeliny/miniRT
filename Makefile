# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 17:23:25 by linyao            #+#    #+#              #
#    Updated: 2025/01/09 00:11:21 by linyao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
NAME_BONUS	= miniRT_bonus
INC			= ./inc/
LIB			= ./lib/
INC_HEADERS	= $(INC)miniRT_bonus.h

FT			= $(LIB)libft/
FT_INC		= $(FT)/libft.h
FT_LNK		= -L$(FT) -lft
FT_LIB		= $(FT)libft.a

SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
OBJ_BONUS_DIR	= ./obj_bonus/

UNAME		= $(shell uname -s)
NUMPROC		= 8

ifeq ($(UNAME), Linux)
	NUMPROC = $(shell grep -c ^processor /proc/cpuinfo)
	LINKFLAGS  = -L./minilibx_linux -lmlx_Linux -L/usr/lib -I./minilibx_linux -lXext -lX11 -lm -lz
	MLX_DIR	= ./minilibx_linux
	MLX_TARGET = libmlx.a
	CFLAGS		= -I $(INC) -I./minilibx_linux -MMD -Wall -Werror -Wextra -O3
#	CFLAGS		= -I $(INC) -I./minilibx_linux -MMD -fsanitize=address -g -Wall -Werror -Wextra -O3
#	LDFLAGS += -fsanitize=address
else ifeq ($(UNAME), Darwin)
	NUMPROC = $(shell sysctl -n hw.ncpu)
	LINKFLAGS	= -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit
	MLX_DIR = ./minilibx_macos
	MLX_TARGET = libmlx.a
	CFLAGS		= -I $(INC) -I./minilibx_macos -MMD -fsanitize=address -g -Wall -Werror -Wextra -O3
	LDFLAGS += -fsanitize=address
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

SRC_FILES	=	main_bonus.c \
				handle_cleanings_bonus.c handle_memory_bonus.c handle_memory1_bonus.c \
				render_rt_bonus.c ctrl_keys_bonus.c utils1_ctrl_bonus.c\
				init_bonus.c init1_bonus.c init2_bonus.c init3_bonus.c \
				init4_bonus.c parser_bonus.c parser1_bonus.c \
				check_bonus.c utils_parse_bonus.c\
				init_pl_elem_bonus.c init_sp_elem_bonus.c init_cy_elem_bonus.c \
				init_cn_elem_bonus.c \
				init_al_elem_bonus.c init_cam_elem_bonus.c init_lit_elem_bonus.c \
				view_bonus.c intersection_bonus.c \
				plane_bonus.c sphere_bonus.c cylinder_bonus.c cylinder1_bonus.c \
				cone_bonus.c \
				ray_bonus.c light_bonus.c shadow_bonus.c rgb_bonus.c \
				utils_bonus.c vec3_utils_bonus.c vec3_utils1_bonus.c \
				checkerboard_bonus.c bump_bonus.c bump1_bonus.c \
				texture_bonus.c texture1_bonus.c matting_bonus.c

				

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_BONUS 	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_BONUS_DIR)%.o, $(SRC))
DEP			= 	$(OBJ:.o=.d)
DEP_BONUS	= 	$(OBJ_BONUS:.o=.d)


all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) $(FT_LIB)
		@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
		@echo "\n${MAGENTA}Minilibx compilation complete$(DEF_COLOR)\n"
#		@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(FT_LNK) $(LINKFLAGS) -o $(NAME)
		@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(FT_LNK) $(LINKFLAGS) -o $@
		@echo "$(GREEN)\n${NAME} created ✓$(DEF_COLOR)\n"

$(NAME_BONUS): $(OBJ_BONUS) $(FT_LIB)
		@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
		@echo "\n${MAGENTA}Minilibx compilation complete$(DEF_COLOR)\n"
		@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_BONUS) $(FT_LNK) $(LINKFLAGS) -o $@
		@echo "$(GREEN)\n${NAME_BONUS} created ✓$(DEF_COLOR)\n"


$(FT_LIB):
		@$(MAKE) -C $(FT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_HEADERS) Makefile
			@mkdir -p $(dir $@)
			@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)%.o: $(SRC_DIR)%.c $(INC_HEADERS) Makefile
			@mkdir -p $(dir $@)
			@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@


-include $(DEP)
-include $(DEP_BONUS)


clean:
			@$(RM) -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
			@make -C $(MLX_DIR) clean
			@make clean -C $(FT)
			@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean:		clean
			@$(RM) -f $(NAME) $(NAME_BONUS)
			@$(RM) -f lib*.a
			@make fclean -C $(FT)
			@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"
#			@$(RM) -rf libmlx.dylib

re:			fclean all


.PHONY:		all clean fclean re bonus
