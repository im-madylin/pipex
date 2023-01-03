/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:58:17 by hahlee            #+#    #+#             */
/*   Updated: 2023/01/03 15:25:29 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	fork_child(t_argvs argvs)
{
	pid_t	pid;
	int		fds[2][2];
	int		i;

	i = 0;
	fds[NEW][READ] = -1;
	fds[NEW][WRITE] = -1;
	while (i <= argvs.cmd_count)
	{
		fds[OLD][READ] = fds[NEW][READ];
		fds[OLD][WRITE] = fds[NEW][WRITE];
		if (i != argvs.cmd_count)
			if (pipe(fds[NEW]) == -1)
				return (-1);
		pid = fork();
		if (pid < 0)
			return (-1);
		else if (pid == 0)
			send_child_func(argvs, fds, i);
		(close(fds[OLD][READ]), close(fds[OLD][WRITE]));
		i++;
	}
	return (pid);
}

void	send_child_func(t_argvs argvs, int fds[][2], int i)
{
	if (i == 0)
		first_child(argvs, fds[NEW]);
	else if (i == argvs.cmd_count)
		last_child(argvs, fds[NEW]);
	else
		middle_child(argvs, fds, i + argvs.cmd1);
}

void	first_child(t_argvs argvs, int fds[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[READ]);
	if (argvs.here_doc)
		fd = open("temp", O_RDWR, 0644);
	else
		fd = open(argvs.argv[1], O_RDWR, 0644);
	if (fd < 0)
		exit_error(1, argvs.argv[1]);
	(dup2(fd, 0), close(fd));
	(dup2(fds[WRITE], 1), close(fds[WRITE]));
	argv = split_com(argvs.argv[argvs.cmd1]);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	check = check_command(argv[0], argvs.envp, &path);
	if (check == -1)
		exit(EXIT_FAILURE);
	execve(path, argv, argvs.envp);
	exit_error(127, argv[0]);
}

void	middle_child(t_argvs argvs, int fds[][2], int index)
{
	char	**argv;
	char	*path;
	int		check;

	(close(fds[OLD][WRITE]), close(fds[NEW][READ]));
	(dup2(fds[OLD][READ], 0), close(fds[OLD][READ]));
	(dup2(fds[NEW][WRITE], 1), close(fds[NEW][WRITE]));
	argv = split_com(argvs.argv[index]);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	check = check_command(argv[0], argvs.envp, &path);
	if (check == -1)
		exit(EXIT_FAILURE);
	else if (check == 0)
		exit_error(127, argv[0]);
	execve(path, argv, argvs.envp);
	exit_error(127, argv[0]);
}

void	last_child(t_argvs argvs, int fds[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[WRITE]);
	check = argvs.argc - 1;
	if (argvs.here_doc)
		fd = open(argvs.argv[check], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(argvs.argv[check], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(1, argvs.argv[check]);
	(dup2(fd, 1), close(fd));
	(dup2(fds[READ], 0), close(fds[READ]));
	argv = split_com(argvs.argv[argvs.argc - 2]);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	check = check_command(argv[0], argvs.envp, &path);
	if (check == -1)
		exit(EXIT_FAILURE);
	execve(path, argv, argvs.envp);
	exit_error(127, argv[0]);
}
