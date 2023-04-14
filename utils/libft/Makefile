CC =		cc
CFLAGS =	-Wall -Wextra -Werror

FILES=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalpha.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
		ft_putchar_fd.c	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c\
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
		ft_tolower.c ft_toupper.c ft_isdigit.c ft_isascii.c ft_isprint.c ft_isalnum.c get_next_line.c get_next_line_utils.c

BONUS=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS =	$(FILES:.c=.o)

BONUSOBJECTS =	$(BONUS:.c=.o)

NAME=	libft.a

all: $(NAME)

bonus: $(BONUSOBJECTS)
	ar -rcs $(NAME) $(BONUSOBJECTS)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:	
	rm -f $(OBJECTS) $(BONUSOBJECTS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re