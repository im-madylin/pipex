/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/23 16:50:38 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h> //

int	first_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[READ]);
	fd = open(file, O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	(dup2(fd, 0), close(fd));
	(dup2(fds[WRITE], 1), close(fds[WRITE]));
	argv = ft_split(com, ' ');
	if (argv == NULL)
		return (-1);
	check = check_command(argv[0], envp, &path);
	if (check == -1)
		return (-1);
	else if (check == 0)
		exit(127);
	execve(path, argv, envp);
	exit(127);
	return (0);
}

int	last_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[WRITE]);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	(dup2(fd, 1), close(fd));
	(dup2(fds[READ], 0), close(fds[READ]));
	argv = ft_split(com, ' ');
	if (argv == NULL)
		return (-1);
	check = check_command(argv[0], envp, &path);
	if (check == -1)
		return (-1);
	else if (check == 0)
		exit(127);
	execve(path, argv, envp);
	exit(127);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fds[2];
	pid_t	pid;
	int		status;
	int		i;

	(void)argv;

	if (argc != 5)
		return (0);
	if (pipe(fds) == -1)
		return (0);
	i = 0;
	while (i < argc - 3)
	{
		pid = fork();
		if (pid > 0)
		{
			//
		}
		else if (pid == 0)
		{
			//
			if (i == 0)
				first_child(argv[1], argv[2], fds, envp);
			else if (i == 1)
				last_child(argv[4], argv[3], fds, envp);
			break ;
		}
		else
			return (0);
		i++;
	}
	close(fds[WRITE]);
	close(fds[READ]);

	int	last_status;
	waitpid(pid, &last_status, 0);
	while(wait(&status) != -1);
	exit (WEXITSTATUS(last_status));
}
