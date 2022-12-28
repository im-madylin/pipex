/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:53 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 22:10:16 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

#include <stdio.h> //
int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		status;
	int		last_status;

	if (argc < 5)
		exit(EXIT_FAILURE);
	pid = fork_child(argc, argv, envp);
	if (pid < 0)
		exit(EXIT_FAILURE);
	// close(fds[NEW][WRITE]);
	// close(fds[NEW][READ]);
	waitpid(pid, &last_status, 0);
	while (wait(&status) != -1)
		continue ;
	exit(WEXITSTATUS(last_status));
}

int	fork_child(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		fds[2][2];
	int		com_i;
	int		i;

	com_i = argc - 4;
	i = 0;
	ft_memset(fds[NEW], -1, 2); //old도 초기화 해야할까?
	while (i <= com_i)
	{
		fds[OLD][READ] = fds[NEW][READ];
		fds[OLD][WRITE] = fds[NEW][WRITE];
		if (i != com_i)
		{
			// if (fds[NEW][READ] != 0 && fds[NEW][WRITE] != 0)
			// {
			// 	fds[OLD][READ] = fds[NEW][READ];
			// 	fds[OLD][WRITE] = fds[NEW][WRITE];
			// }
			if (pipe(fds[NEW]) == -1)
				exit(EXIT_FAILURE);
			printf("open %d : %d, %d\n", i, fds[NEW][READ], fds[NEW][WRITE]);
		}
		pid = fork();
		if (pid < 0)
			return (-1);
		else if (0 < pid)
		{
			printf("close %d : %d, %d\n", i, fds[NEW][READ], fds[NEW][WRITE]);
			(close(fds[NEW][READ]), close(fds[NEW][WRITE]));
			i++;
			continue;
		}
		else if (pid == 0)
		{
			if (i == 0)
				first_child(argv[1], argv[2], fds[NEW], envp);
			else if (i == com_i)
				last_child(argv[argc - 1], argv[argc - 2], fds[OLD], envp);
			else
				middle_child(argv[i + 2], fds, envp);
		}
	}
	return (pid);
}

void	first_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	printf("<first>\n");
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

void	middle_child(char *com, int fds[][2], char *envp[])
{
	char	**argv;
	char	*path;
	int		check;

	printf("<middle>\n");
	(close(fds[OLD][WRITE]), close(fds[NEW][READ]));
	(dup2(fds[OLD][READ], 0), close(fds[OLD][READ]));
	(dup2(fds[NEW][WRITE], 1), close(fds[NEW][WRITE]));
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

	printf("<last>\n");
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

