CC = cc
CFLAGS = -Ofast -g #-Wall -Wextra -Werror 
NAME = cub3d_bonus
LINKED_LIST = ../libraries/linked_list
GET_NEXT_LINE = ../libraries/get_next_line
LIBFT = ../libraries/libft
MLX42 = ../libraries/MLX42/build

OS := $(shell uname)
ifeq ($(OS), Linux)
    LDLFLAGS = -lmlx42 -lll -lgnl -lft -L$(LINKED_LIST) -L $(LIBFT) -L$(GET_NEXT_LINE) -L$(MLX42) -ldl -lglfw -pthread -lm
else
    LDLFLAGS = -lmlx42 -lll -lgnl -lft -L$(LINKED_LIST) -L $(LIBFT) -L$(GET_NEXT_LINE) -L$(MLX42) -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib
endif

SOURCES = src/main.c\
	src/util/ft_isspace2.c\
	src/util/strutil.c\
	src/util/werror.c\
	src/util/ternary.c\
	src/util/ft_isnumber.c\
	src/util/ft_realloc.c\
	src/util/clear_global.c\
	src/minimap/minimap.c\
	src/minimap/minimap_util.c\
	src/parsing/parsing.c\
	src/parsing/map_parsing.c\
	src/parsing/map_parsing_util.c\
	src/parsing/sanitization.c\
	src/parsing/sanitization_util.c\
	src/parsing/util.c\
	src/geometry/raycasting.c\
	src/geometry/raycasting_util.c\
	src/geometry/line_drawing.c\
	src/geometry/projection.c\
	src/geometry/projection_util.c\
	src/geometry/angle_util.c\
	src/movement/movement.c\
	src/movement/movement_keys.c\
	src/movement/door_logic.c\
	src/movement/door_logic_util.c\
	src/sprite.c

	

HEADERS = ../includes/cub3d_bonus.h
OBJECTS = $(SOURCES:.c=.o)

COLOR_OFF=\033[0m
BLACK=\033[1;30m
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
PURPLE=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m

all : ../$(NAME)

../$(NAME) : $(OBJECTS)
	@printf "${BLUE}Linking\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDLFLAGS)
	@printf "${GREEN}Done Making $(NAME).                        ${COLOR_OFF}\n"

%.o : %.c $(HEADERS)
	@printf "${BLUE}Compiling $<...\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -I../includes -c $< -o $@

clean :
	@rm -f $(OBJECTS)
	@printf "${RED}Removed $(NAME) object files.${COLOR_OFF}\n"

fclean :
	@rm -f $(OBJECTS) ../$(NAME) 
	@printf "${RED}Removed $(NAME) object files and $(NAME) binary.${COLOR_OFF}\n"

re : fclean all

.PHONY : fclean re clean all