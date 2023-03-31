#include "kerem.h"

// test pipes
/*
int	main(void)
{
	char	***argv;
	char	**splitted;
	char	*str;
	int		x;
	int		i;

	// str = ft_strdup("cat test.c | tr -cs a-zA-Z \n | tr A-Z a-z | sort | uniq -c | sort -rn | head -n 5");
	str = ft_strdup("echo 42 | cat -e");
	splitted = ft_split(str, '|');
	free(str);
	x = 0;
	while (splitted[x] != NULL)
	{
		str = ft_strtrim(splitted[x], " ");
		free(splitted[x]);
		splitted[x] = str;
		x++;
	}
	argv = malloc((x + 1) * sizeof(char **));
	argv[x] = NULL;
	i = 0;
	while (i < x)
	{
		argv[i] = ft_split(splitted[i], ' ');
		i++;
	}
	i = 0;
	x = 1;
	if (ft_pipe(argv, x) == -1)
		return (1);
	while (i < x)
	{
		ft_free(argv[i]);
		i++;
	}
	ft_free(splitted);
	free(argv);
	return (0);
}
*/

// test heredoc
/*
int	main(void)
{
	char	**argv;
	int		pid;

	here_doc("- EOF");
	argv = ft_split("cat .heredoc_data", ' ');
	pid = fork();
	if (pid == 0)
	{
		ft_exec(argv);
		exit(1);
	}
	else
		wait(NULL);
	unlink(".heredoc_data");
	free (argv);
	return (0);
}
*/

// test ft_exec
// /*
int	main(int argc, char *argv[])
{
	// char	**argv;
	int		pid;

	if (argc < 2)
	{
		perror("Error: ");
		return (1);
	}
	// argv = ft_split("ls -la", ' ');
	pid = fork();
	if (pid == 0)
	{
		ft_exec(argv + 1);
		// ft_free(argv);
	}
	else
		wait(NULL);
	return (0);
}
// */

// test redirections
/*
int	main(void)
{
	char	**argv;
	int		fd;
	int		pid;
	int		fileno;
	char	mode;

	mode = 'a';
	fileno = 1;
if (fileno == 1)
{
//	if prompt is "echo Hello World >> hello.txt", then
	fd = redirect(" hello.txt", fileno, mode);
	argv = ft_split ("echo Hello World ", ' ');
}
else
{
//	if prompt is "cat < hello.txt", then:
	fd = redirect(" hello.txt", fileno, 'n');
	argv = ft_split("cat ", ' ');
}
	pid = fork();
	if (pid == 0)
	{
		ft_exec(argv);
		exit(1);
	}
	else
		wait(NULL);
	free (argv);
	dup2(fd, fileno);
	ft_printf("Done!\n");
	return (0);
}
*/