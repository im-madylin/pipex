/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/22 22:19:41 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h> //

char	*check_command(char *com, char *envp[])
{
	//access로 커맨드 정상여부 확인
	//$PATH의 경로를 추출해오는 방법 확인해서, 콜론을 기준으로 쪼개 명령어 앞에 붙이고 access 검증
	(void)com;
	(void)envp;
	return (0);
}

int	first_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;

	close(fds[READ]);
	fd = open(file, O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	(dup2(fd, 0), close(fd));
	(dup2(fds[WRITE], 1), close(fds[WRITE]));
	argv = ft_split(com, ' ');
	if (argv == NULL)
		return (-1);
	path = check_command(argv[0], envp);
	if (path == NULL)
		return (-1); //or exit(127)
	execve(path, argv, envp);
	exit(127);
	return (0);
}

int	last_child(char *file, char *com, int fds[], char *envp[])
{
	char	**argv;
	char	*path;
	int		fd;

	close(fds[WRITE]);
	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	(dup2(fd, 1), close(fd));
	(dup2(fds[READ], 0), close(fds[READ]));
	argv = ft_split(com, ' ');
	if (argv == NULL)
		return (-1);
	path = check_command(argv[0], envp);
	if (path == NULL)
		return (-1); //or exit(127)
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
