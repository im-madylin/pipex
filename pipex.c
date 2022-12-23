/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/23 13:39:44 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h> //

int	check_command(char *com, char *envp[], char **result)
{
	char	**path;
	char	*temp;
	int		i;

	if (access(com, X_OK) == 0)
	{
		*result = com;
		return (1);
	}
	path = split_envp(envp);
	if (path == NULL)
		return (-1);
	temp = ft_strjoin("/", com);
	if (temp == NULL)
		return (double_free(path, -1));
	i = 0;
	while(path[i])
	{
		*result = ft_strjoin(path[i], temp);
		if (*result == NULL)
			return (double_free(path, -1), safety_free(temp, -1));
		if (access(*result, X_OK) == 0)
			return (double_free(path, 1), safety_free(temp, 1));
		safety_free(*result, 0);
		i++;
	}
	return (double_free(path, 0), safety_free(temp, 0));
}

int	double_free(char **str, int result)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (result);
}

int	safety_free(char *str, int result)
{
	free(str);
	str = NULL;
	return (result);
}

char	**split_envp(char *envp[])
{
	char	**path;
	char	*temp;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		temp = ft_strnstr(envp[i], "PATH=", -1);
		if (temp != NULL)
		{
			path = ft_split(temp + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}

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
	//int		status;
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
			printf("parents %d, %d\n", pid, i);
		}
		else if (pid == 0)
		{
			printf("child %d\n", i);
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
	// if (pid > 0)
	// 	while(wait(&status) != -1); 무한로딩 됨
	return (0);
}
