/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 18:43:54 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fds[2];
	pid_t	pid;
	int		status;
	int		last_status;

	if (argc != 5)
		exit(EXIT_FAILURE);
	if (pipe(fds) == -1)
		exit(EXIT_FAILURE);
	pid = fork_child(argc, argv, envp, fds);
	if (pid < 0)
		exit(EXIT_FAILURE);
	close(fds[WRITE]);
	close(fds[READ]);
	waitpid(pid, &last_status, 0);
	while (wait(&status) != -1)
		continue ;
	exit(WEXITSTATUS(last_status));
}

int	fork_child(int argc, char *argv[], char *envp[], int fds[])
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < argc - 3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_child(argv[1], argv[2], fds, envp);
			else if (i == 1)
				last_child(argv[4], argv[3], fds, envp);
			break ;
		}
		else if (pid < 0)
			return (-1);
		i++;
	}
	return (pid);
}

void	first_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[READ]);
	fd = open(file, O_RDWR, 0644);
	if (fd == -1)
		exit_error(1, file);
	(dup2(fd, 0), close(fd));
	(dup2(fds[WRITE], 1), close(fds[WRITE]));
	argv = split_com(com);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	check = check_command(argv[0], envp, &path);
	if (check == -1)
		exit(EXIT_FAILURE);
	else if (check == 0)
		exit_error(127, argv[0]);
	execve(path, argv, envp);
	exit_error(127, argv[0]);
}

void	last_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[WRITE]);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(1, file);
	(dup2(fd, 1), close(fd));
	(dup2(fds[READ], 0), close(fds[READ]));
	argv = split_com(com);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	check = check_command(argv[0], envp, &path);
	if (check == -1)
		exit(EXIT_FAILURE);
	else if (check == 0)
		exit_error(127, argv[0]);
	execve(path, argv, envp);
	exit_error(127, argv[0]);
}
