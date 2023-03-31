.PHONY: all clean fclean re make-libft clean-libft fclean-libft

NAME = test
OBJECTS = $(SRCS:.c=.o)

SRCS := test.c ft_pipe.c here_doc.c redirect.c ft_exec.c

all: make-libft $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(OBJECTS) -g -o $(NAME) libft/libft.a

$(OBJECTS): $(SRCS)
	@gcc -c $^ -g -Wall -Wextra -Werror

make-libft:
	@bash -c "make -s -C ./libft"

clean-libft:
	@bash -c "make clean -s -C ./libft"

fclean-libft:
	@bash -c "make rm-name -s -C ./libft"

run:
	@./$(NAME)

leak:
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

clean: clean-libft
	@rm -f $(OBJECTS) $(BNSOBJECTS)

fclean: clean fclean-libft
	@rm -f $(NAME) $(BNSNAME) play playground.o

re: fclean all
