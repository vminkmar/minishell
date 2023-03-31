#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "termios.h"
# include <sys/wait.h>

# define PIPE1 "pipe_data1"
# define PIPE2 "pipe_data2"

int g_status;

enum e_type
{
	RANDOM,
	QUOTES,
	D_QUOTES,
	REDIR_IN,
	D_REDIR_IN,
	REDIR_OUT,
	D_REDIR_OUT,
	WORD,
	QVAR,
	UQVAR,
};

enum e_state
{
	NORMAL,
	DQ,
	SQ,
};

enum e_argument
{
	ANYTHING,
	COMMAND,
	OPTION,
	ARGUMENT,
	FILENAME,
	REDI,
};

typedef struct s_token
{
	enum e_type		type;
	enum e_state	state;
	enum e_argument	argument;
	char			*content;
	struct s_token	*next;
} t_token;

typedef struct s_cmd
{
	int				out;
	int 			in;
	t_token 		*head;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_env
{
	char			*value;
	char 			*name;
	struct s_env	*next;
} t_env;

typedef struct s_con
{
	int i;
	int k;
	enum e_state status;

} t_con;

typedef struct s_execute
{
	char	***commands;
	int		pipes;
	int		pipe_num;
	int		pipes_fd[2];
	int		tmp_fd;
	int		out;
	int		in;

} t_execute;

void print_linked_list(t_cmd *cmd);





void	create_first_cmd(t_cmd **cmd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
int		is_sign(char c);
int		is_whitespace(char c);
int		is_quoted(char c);
int		search_sign(char *str, int sign);
int		ft_strcmp(const char *s1, const char *s2);

// parser
t_cmd	*parse_stuff(t_cmd *cmd);
int	check_sq(t_token *tmp, int *i);
int	check_dq(t_token *tmp, int *i);
int	look_quotes(char *str);
int	compare_char(char *str, char c);
int	ft_strcmp(const char *s1, const char *s2);
int	check_quotes(t_token *token);
char	*make_it_small(char *str);
int	check_token_and_variables(t_token *tmp, t_cmd *search);
void	check_command(t_cmd *cmd);
void	check_rd_out(t_token *tmp);
void	check_rd_in(t_token *tmp);

//buildins
void execute_env(t_env *node);
t_env *new_node(char *a[], t_env **node);


//signal
void signal_handler(int sig);


//set_env
void	lstadd_back_new_node(t_env **lst, t_env *new);
void	set_env(char *env[], t_env **node);

//set_env_utils
char	**split_env(char const *s, char c);

//export
int	execute_export(t_cmd *cmd, t_env **node);
void	add_node(char *a[], t_env **node);


//expander
char *remove_dq(char *str, int *i);
char *remove_sq(char *str, int *i);
char **get_words(char *str, char **value, int length);
int get_number(char *str, int length);
char *remove_variable(char *str);
char *remove_dollar(char *str);
char	*stupid_shit( char *s1, char *s2);
char *change_value(char **str, t_env *env, int i, int j);
char *expand_var(char *str, t_env *env, int i);
char *get_value(char *value, char *str);
int expander(t_cmd *cmd, t_env *env);

//expander_utils
int is_valid(char c);
char	*sl_strjoin(char *s1, char *s2);


//error_management
void free_cmd_token(t_cmd **cmd);
void free_all(t_env **node);
void free_list(t_cmd **cmd);
void print_error(char *str);


// lexer
int		lexer(char *input, t_cmd *cmd);
void	lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	lstadd_back_token(t_token **lst, t_token *new);
int		check_for_token_for_redirections(char *input, t_cmd *cmd, t_con *con);
int		add_if_pipe(char *input, t_cmd *cmd, t_con *con);
t_cmd	*check_for_pipes(t_cmd *cmd);
int		check_for_redirecions(char *input, t_cmd *cmd, t_con *con);
int		check_for_words(char *input, t_cmd *cmd, t_con *con);
int		lexer_whitespace(char *input, t_cmd *cmd, t_con *con);
int		skip_whitespaces(char *input, t_con *con);
int		check_for_words(char *input, t_cmd *cmd, t_con *con);
int		check_for_dq(char *input, t_cmd *cmd, t_con *con);
int		check_for_sq(char *input, t_cmd *cmd, t_con *con);

// lexer_utils
void create_first_cmd(t_cmd **cmd);
void create_cmd(t_cmd **cmd);
t_token *create_token(char *j);
void add_token(t_cmd *cmd, char *j);

//connector
int connector(char *input, t_cmd *cmd, t_env *env);
char ***linked_to_char(t_cmd *cmd, t_execute exec);
int		get_command(t_cmd *cmd, t_env *node, t_execute exec, char **env);
int	compare_cmd(t_cmd *cmd, t_env *node);
int look_out_for_command(t_cmd *cmd);
char	*here_doc(char *eof, char suppress);



//executor
void executor(t_execute *exec);
// void get_token(char *input, t_cmd *cmd);
// void create_cmd(t_cmd **cmd);
// t_token *create_token(char *j);
// void add_token(t_cmd *cmd, char *j);
int count_pipes(t_cmd *cmd);
void	ft_exec(char *argv[], char **env, t_env *node);
int	redirect(char *str, int fileno, char mode);
int	ft_pipe(t_cmd *cmd, t_env *node, t_execute exec, char **env);
char *search_env(char *name, t_env *node);
void free_exec(char ***array);
int		execute(t_execute *exec, char **env, t_env *node, t_cmd *cmd);
int		execute_last(t_execute *exec, char **env, t_env *node, t_cmd *cmd);
int		execute_without_pipes(t_execute *exec, char **env, t_env *node, t_cmd *cmd);



//pipes


#endif