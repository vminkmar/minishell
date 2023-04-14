NAME			:=	minishell

CC				:=	cc

FILES			:=	lexer.c main.c signal.c set_env.c utils.c parser.c execute_stuff.c connector.c error_management.c\
					expander.c lexer_utils.c expander_utils.c buildins.c set_env_utils.c lexer_pipes_redirections.c\
					lexer_check_quotes.c lexer_whitespaces_words.c parser_quotes.c parser_utils.c parser_redirections.c\
					parser_tokens.c expander_quotes.c expander_var.c utils_utils.c ft_exec.c export.c pipes.c redirections.c\
					here_doc.c connector_free.c expand_variables.c expand_variables_utils.c expander_checks_dollar.c\
					expander_get_words.c expander_var_utils.c export_utils.c pipes_utils.c compare_cmd.c buildins_utils.c\
					execute_echo.c

RM				:=	rm -f

HEADER			:=	-I./include

VPATH			:=	src/ src/executor src/connector src/expander src/lexer src/parser src/redirections src/utils

LINK_FLAGS		:=

ODIR			:=	obj

OBJS			:=	$(FILES:%.c=$(ODIR)/%.o)

DOWNLOADFOLDER	:=	utils/readline/dwnlds

LIBFT			:=	utils/libft

LFT				:=	utils/libft/libft.a

LFLAGS 			:=	 -L $(DOWNLOADFOLDER)/readline_out/lib -lreadline

CFLAGS			:=	-Wall -Werror -Wextra -g -I $(DOWNLOADFOLDER)/readline_out/include

all:  $(NAME)

$(LFT):	$(LIBFT)
	$(MAKE) -C $(LIBFT) --silent

$(NAME): $(DOWNLOADFOLDER) $(OBJS) $(LFT)
	$(CC) $(CFLAGS) $(LFT) $(OBJS) $(LINK_FLAGS) $(LFLAGS) -o $@

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

norm:
	norminette src/ include/ utils/libft

clean:
	$(MAKE) -C $(LIBFT) clean
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME) $(LFT)

re: fclean all

run:
	@./minishell

.PHONY: all clean fclean re run norm


LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif

lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer

$(DOWNLOADFOLDER):
	mkdir -p $(DOWNLOADFOLDER)
	curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz
	tar xfz $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz -C $(DOWNLOADFOLDER)
	cd $(DOWNLOADFOLDER)/readline-8.1.2; ./configure --prefix=$(PWD)/$(DOWNLOADFOLDER)/readline_out; cd ../../
	$(MAKE) -C $(DOWNLOADFOLDER)/readline-8.1.2
	$(MAKE) install -C $(DOWNLOADFOLDER)/readline-8.1.2
