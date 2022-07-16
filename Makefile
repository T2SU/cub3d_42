# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 12:02:21 by smun              #+#    #+#              #
#    Updated: 2022/07/16 20:36:16 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -rf
#CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIB_MLX = libmlx.dylib
INC = -I$(MLX_DIR) -I./libft
LIB = -L./libft -L. -lft -lmlx -framework OpenGL -framework AppKit -lz

NAME = cub3D

##  Part. Mandatory   Source Codes

M_DIR = ./mandatory/
M = \
	main \
	base/app \
	base/error \
	base/device \
	base/image \
	base/resources \
	base/tick \
	map/map \
	map/map_load \
	map/map_load_info \
	map/map_load_field \
	map/map_load_entity \
	map/elem_read \
	map/map_validate \
	map/map_func \
	map/block \
	entity/entity \
	entity/entity_const \
	entity/player \
	input/key \
	input/mouse \
	output/bmp \
	graphic/draw \
	graphic/screen \
	graphic/project \
	graphic/project_wall \
	graphic/project_sprite \
	type/point \
	type/size \
	type/rect \
	type/vector \
	type/vector_arith \
	type/vector_trans \
	util/util \
	util/util_qsort \
	util/geometry \
	util/util_file \
	util/util_atoi
M_SRC = $(addprefix $(M_DIR), $(addsuffix .c, $(M)))
OBJ = $(M_SRC:.c=.o)

##  Part. Bonus  Source Codes (Additional files as a bonus)

B_DIR = ./bonus/
B = \
	base/window \
	base/texset_load \
	base/texset_sprite \
	base/cheat \
	entity/player_item \
	entity/player_game \
	entity/entity_life \
	entity/entity_life_ai \
	entity/entity_life_ai_attack \
	entity/entity_life_appearance \
	entity/entity_life_const \
	graphic/project_skybox \
	graphic/screen_colormap \
	map/block2 \
	map/map_architect \
	map/map_load_facility \
	facility/facility \
	facility/door \
	facility/secret \
	facility/exit \
	util/geometry_raycast \
	util/geometry_raycast_facility \
	util/geometry_raycast_life \
	util/util_real \
	util/util_list \
	util/util_random \
	hud/hud \
	hud/hud_const \
	hud/hud_digit \
	hud/hud_weapon \
	hud/hud_lifebar \
	hud/hud_text \
	weapon/weapon \
	weapon/weapon_player \
	sound/sound \
	sound/sound_const
B_SRC = $(addprefix $(B_DIR), $(addsuffix _bonus.c, $(M) $(B)))
BOBJ = $(B_SRC:.c=.o)

##  Include Directory

ifeq ($(MAKECMDGOALS), bonus)
	INCCUB3D = -I$(B_DIR)
	MLX_DIR = ./minilibx_mms_20210621
else ifeq ($(MAKECMDGOALS), creb)
	INCCUB3D = -I$(B_DIR)
	MLX_DIR = ./minilibx_mms_20210621
else
	INCCUB3D = -I$(M_DIR)
	MLX_DIR = ./minilibx_mms_20210621
endif

## ALL

all : $(NAME)


## cub3D  Clean, FullClean, Re, BonusRe

cclean :
	rm -rf $(OBJ) $(BOBJ)

cfclean : cclean
	rm -rf $(NAME)

cre : cfclean $(NAME)

creb : cfclean bonus


## Common Instruction  Clean, FullClean, Re

clean : cclean
	$(MAKE) $@ -C libft
	$(RM) $(RMFLAGS) $(LIB_MLX)
	$(MAKE) $@ -C $(MLX_DIR)

fclean : clean cfclean
	$(MAKE) $@ -C libft

re : fclean all


## Objects Compile

%.o : %.c
	$(CC) $(CFLAGS) $(INCCUB3D) $(INC) -c $< -o $@

## Binary Creation

$(NAME) : ./libft/libft.a ./$(LIB_MLX) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(LIB) $(OBJ)

# install_name_tool -change $(LIB_MLX) "@loader_path/$(MLX_DIR)/$(LIB_MLX)" $(NAME)

bonus : ./libft/libft.a ./$(LIB_MLX) $(BOBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(LIB) $(BOBJ)
# install_name_tool -change $(LIB_MLX) "@loader_path/$(MLX_DIR)/$(LIB_MLX)" $(NAME)

## Libraries

./$(LIB_MLX):
	$(MAKE) -C $(MLX_DIR)
	mv ./$(MLX_DIR)/$(LIB_MLX) ./

./libft/libft.a :
	$(MAKE) -C libft


## Norminette for convinient

norme:
	$(MAKE) $@ -C libft
	norminette $(M_SRC) $(B_SRC) $(M_DIR)cub3d.h $(B_DIR)cub3d_bonus.h $(M_DIR)typedef.h $(B_DIR)typedef_bonus.h


## .PHONY

.PHONY: all clean fclean re bonus norme cclean cfclean cre creb
