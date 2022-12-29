/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:53 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/29 16:42:52 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

#include <stdio.h> //
int	main(int argc, char *argv[], char *envp[])
{	
	t_argvs	argvs;
	pid_t	pid;
	int		status;
	int		last_status;

	if (argc < 5)
		exit(EXIT_FAILURE);
	ft_memset(&argvs, 0, sizeof(argvs));
	if (ft_strnstr(argv[1], "here_doc", -1) != NULL)
	{
		if (argc < 6)
			exit(EXIT_FAILURE);
		argvs.here_doc = 1;
	}
	argvs.argc = argc;
	argvs.argv = argv;
	argvs.envp = envp;
	pid = fork_child(argvs);
	if (pid < 0)
		exit(EXIT_FAILURE);
	waitpid(pid, &last_status, 0);
	while (wait(&status) != -1)
		continue ;
	exit(WEXITSTATUS(last_status));
}

int	fork_child(t_argvs argvs)
{
	pid_t	pid;
	int		fds[2][2];
	int		last_com;
	int		i;

	last_com = argvs.argc - 4;
	i = 0;
	fds[NEW][READ] = -1;
	fds[NEW][WRITE] = -1;
	while (i <= last_com)
	{
		fds[OLD][READ] = fds[NEW][READ];
		fds[OLD][WRITE] = fds[NEW][WRITE];
		if (i != last_com)
			if (pipe(fds[NEW]) == -1)
				exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			return (-1);
		else if (pid == 0)
		{
			if (i == 0)
				first_child(argvs, fds[NEW]);
			else if (i == last_com)
				last_child(argvs, fds[NEW]);
			else
				middle_child(argvs, fds, i + 2);
		}
		(close(fds[OLD][READ]), close(fds[OLD][WRITE]));
		i++;
	}
	return (pid);
}

void	first_child(t_argvs argvs, int fds[])
{
	char	**argv;
	char	*path;
	int		fd;
	int		check;

	close(fds[READ]);
	fd = open(argvs.argv[1], O_RDWR, 0644);
	if (fd == -1)
		exit_error(1, argvs.argv[1]);
	(dup2(fd, 0), close(fd));
	(dup2(fds[WRITE], 1), close(fds[WRITE]));
	argv = split_com(argvs.argv[2]);
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
	fd = open(argvs.argv[argvs.argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(1, argvs.argv[argvs.argc - 1]);
	(dup2(fd, 1), close(fd));
	(dup2(fds[READ], 0), close(fds[READ]));
	argv = split_com(argvs.argv[argvs.argc - 2]);
	if (argv == NULL)
		exit(EXIT_FAILURE);
	check = check_command(argv[0], argvs.envp, &path);
	if (check == -1)
		exit(EXIT_FAILURE);
	else if (check == 0) //없어도 됨
		exit_error(127, argv[0]);
	execve(path, argv, argvs.envp);
	exit_error(127, argv[0]);
}

