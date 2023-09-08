CC = cc
CFLAGS = 
NAME = cub3d
LINKED_LIST = libraries/linked_list
GET_NEXT_LINE = libraries/get_next_line
LIBFT = libraries/libft
MLX42 = libraries/MLX42/build
LDLFLAGS = -lmlx42 -lll -lgnl -lft -L$(LINKED_LIST) -L$(LIBFT) -L$(GET_NEXT_LINE) -L$(MLX42) -ldl -lglfw -pthread -lm
SOURCES = src/test.c
HEADERS = MLX42.h MLX42_Int.h
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

all : $(NAME)

$(NAME) : $(OBJECTS)
	@make -C $(LINKED_LIST) --no-print-directory
	@make -C $(GET_NEXT_LINE) --no-print-directory
	@make -C $(LIBFT) --no-print-directory
	@$(bash cd libraries/MLX42 && cmake -B build && cmake --build build -j4 && exit 0)
	@printf "${BLUE}Linking\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDLFLAGS)
	@printf "${GREEN}Done Making Minishell.                        ${COLOR_OFF}\n"

%.o : %.c $(HEADER)
	@printf "${BLUE}Compiling $<...\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	@rm -f $(OBJECTS)
	@printf "${RED}Removed minishell object files.${COLOR_OFF}\n"
	@make -C $(LIBFT) clean --no-print-directory 
	@make -C $(LINKED_LIST) clean --no-print-directory 
	@make -C $(GET_NEXT_LINE) clean --no-print-directory 

fclean :
	@rm -f $(OBJECTS) $(NAME) 
	@printf "${RED}Removed minishell object files and Minishell binary.${COLOR_OFF}\n"
	@make -C $(LIBFT) fclean --no-print-directory 
	@make -C $(LINKED_LIST) fclean --no-print-directory 
	@make -C $(GET_NEXT_LINE) fclean --no-print-directory 

re : fclean all

.PHONY : fclean re clean all