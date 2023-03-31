/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:20:51 by vminkmar          #+#    #+#             */
/*   Updated: 2023/03/31 19:09:21 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_vars()
{
	struct termios term_settings;

	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_cflag &= ~(IEXTEN | ECHOCTL);
   	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
	g_status = 0;
}





void print_linked_list(t_cmd *cmd)
{
    while (cmd)
    {
        t_token *token = cmd->head;
        while (token)
        {
            ft_putstr_fd(token->content, 2);
			ft_putstr_fd("\n", 2);
			// printf("%u\n", token->type);
			// printf("%u\n", token->argument);
            token = token->next;
        }
		cmd = cmd->next;
		printf("\n\n");
    }
}

// void	print_linked_list(t_env *node)
// {
//     while (node)
//     {
//             printf("%s=%s\n", node->name, node->value);
//             node = node->next;
//     }
// }



void	end_shell(t_env **node)
{
	free_all(node);
	clear_history();
	if (isatty(STDIN_FILENO))
	{
		printf("\n");
		printf("exit");
	}
	exit(0);
}

char *get_input(char *input, t_env *node)
{;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	if (isatty(STDIN_FILENO))
		input = readline("\033[0;32mMINISHELL-1.0$ \033[0;0m");
	else
		input = get_next_line(STDIN_FILENO);
	if (input == NULL)
		end_shell(&node);
	if (ft_strcmp(input, "") == 0)
	{
		rl_on_new_line();
		return (NULL);
	}
	add_history(input);
	return (input);
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	t_env	*node;
	char	*input;

	(void)argc;
	(void)argv;
	cmd = NULL;
	node = NULL;
	input = NULL;
	set_env(env, &node);
	init_vars();
	while (1)
	{
		input = get_input(input, node);
		if (input == NULL)
			continue ;
		// input = "ls | wc > test";
		create_first_cmd(&cmd);
		if(connector(input, cmd, node) == 1)
			free_cmd_token(&cmd);
		// print_linked_list(cmd);
		free(input);
		free_list(&cmd);
	}
	return (0);
}
