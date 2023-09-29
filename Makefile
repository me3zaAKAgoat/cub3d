LINKED_LIST = libraries/linked_list
GET_NEXT_LINE = libraries/get_next_line
LIBFT = libraries/libft
MLX42 = libraries/MLX42/build

MLX42_LIB = libraries/MLX42/build/libmlx42.a 

COLOR_OFF=\033[0m
BLACK=\033[1;30m
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
PURPLE=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m

all: $(MLX42_LIB)
	@make -C $(LINKED_LIST) --no-print-directory
	@make -C $(GET_NEXT_LINE) --no-print-directory
	@make -C $(LIBFT) --no-print-directory
	@make -C mandatory --no-print-directory

$(MLX42_LIB) :
	@echo 'cd libraries/MLX42 && cmake -B build > /dev/null && (printf "${GREEN}MLX42 build was setup successfully.${COLOR_OFF}\n" || "${RED}MLX42 build setup failed.${COLOR_OFF}\n") && cmake --build build -j4 > /dev/null && (printf "${GREEN}MLX42 built successfully.${COLOR_OFF}\n" || "${RED}MLX42 build failed.${COLOR_OFF}\n")' | bash

bonus: $(MLX42_LIB)
	@make -C $(LINKED_LIST) --no-print-directory
	@make -C $(GET_NEXT_LINE) --no-print-directory
	@make -C $(LIBFT) --no-print-directory
	@make -C bonus --no-print-directory

clean :
	@printf "${RED}removed MLX42 library.${COLOR_OFF}\n"	
	@rm -rf $(MLX42_LIB)
	@make clean -C mandatory --no-print-directory
	@make clean -C bonus --no-print-directory
	@make -C $(LIBFT) clean --no-print-directory 
	@make -C $(LINKED_LIST) clean --no-print-directory 
	@make -C $(GET_NEXT_LINE) clean --no-print-directory 

fclean :
	@printf "${RED}removed MLX42 build.${COLOR_OFF}\n"	
	@rm -rf $(MLX42)
	@make -C $(LIBFT) fclean --no-print-directory 
	@make -C $(LINKED_LIST) fclean --no-print-directory 
	@make -C $(GET_NEXT_LINE) fclean --no-print-directory 
	@make fclean -C mandatory --no-print-directory
	@make fclean -C bonus --no-print-directory

re : fclean all

.PHONY : fclean re clean all bonus
