/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:53 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/30 17:25:48 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{	
	t_argvs	argvs;
	pid_t	pid;
	int		status;
	int		last_status;

	if (argc < 5)
		exit(EXIT_FAILURE);
	ft_memset(&argvs, 0, sizeof(argvs));
	if (set_argvs_struct(&argvs, argc, argv, envp) == -1)
		exit(EXIT_FAILURE);
	pid = fork_child(argvs);
	if (pid < 0)
		exit(EXIT_FAILURE);
	unlink("temp");
	waitpid(pid, &last_status, 0);
	while (wait(&status) != -1)
		continue ;
	exit(WEXITSTATUS(last_status));
}

int	set_argvs_struct(t_argvs *argvs, int argc, char *argv[], char *envp[])
{
	argvs->argc = argc;
	argvs->argv = argv;
	argvs->envp = envp;
	argvs->cmd1 = 2;
	argvs->cmd_count = argc - 4;
	if (!ft_strncmp(argv[1], "here_doc", -1))
	{
		if (argc < 6)
			return (-1);
		argvs->cmd1 = 3;
		argvs->here_doc = 1;
		if (get_here_doc(argv[2]) == -1)
			return (-1);
	}
	return (0);
}

int	get_here_doc(char *limiter)
{
	int		fd;
	char	*tmp;

	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		write(1, "here_doc> ", 10);
		tmp = get_next_line(0);
		if (tmp == NULL)
		{
			close(fd);
			unlink("temp");
			return (-1);
		}
		if (!ft_strncmp(tmp, limiter, ft_strlen(limiter)))
		{
			safety_free(&tmp, 0);
			break ;
		}
		write(fd, tmp, ft_strlen(tmp));
		safety_free(&tmp, 0);
	}
	return (close(fd));
}

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
	if (argvs.here_doc)
		fd = open(argvs.argv[argvs.argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
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
	execve(path, argv, argvs.envp);
	exit_error(127, argv[0]);
}
