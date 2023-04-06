/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminkmar <vminkmar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:20:51 by vminkmar          #+#    #+#             */
/*   Updated: 2023/04/06 17:55:03 by vminkmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(void)
{
	struct termios	term_settings;

	g_status = 0;
	tcgetattr(STDIN_FILENO, &term_settings);
	term_settings.c_cflag &= ~(IEXTEN | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_settings);
}

void	end_shell(t_env **node)
{
	free_all(node);
	clear_history();
	if (isatty(STDIN_FILENO))
	{
		printf("\n");
		printf("exit");
	}
	exit(g_status);
}

char	*get_input(char *input, t_env *node)
{
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
	if (set_env(env, &node) == EXIT_FAILURE)
		exit(1);
	init_vars();
	while (1)
	{
		input = get_input(input, node);
		if (input == NULL)
			continue ;
		// input = "cd \"$PWD/file_tests\"";
		create_first_cmd(&cmd);
		connector(input, cmd, node);
		free(input);
		free_list(cmd);
		cmd = NULL;
	}
	free_all(&node);
	return (g_status);
}
