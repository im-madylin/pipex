/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/22 21:10:37 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h> //

int	check_command(char *com)
{
	//access로 커맨드 정상여부 확인
	//$PATH의 경로를 추출해오는 방법 확인해서, 콜론을 기준으로 쪼개 명령어 앞에 붙이고 access 검증
	(void)com;
	return (0);
}

int	first_child(char *file, char *com, int fds[])
{
	int	fd;
	char	**argv;

	close(fds[READ]);
	fd = open(file, O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	(dup2(fd, 0), close(fd));
	(dup2(fds[WRITE], 1), close(fds[WRITE]));
	argv = ft_split(com, ' ');
	// if (check_command(com) == -1)
	// 	return (-1);
	execve("/bin/cat", argv, NULL);
	exit(127); //command notfound..
	return (0);
}

int	last_child(char *file, char *com, int fds[])
{
	int	fd;
	char	**argv;

	close(fds[WRITE]);
	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	(dup2(fd, 1), close(fd));
	(dup2(fds[READ], 0), close(fds[READ]));
	argv = ft_split(com, ' ');
	// if (check_command(com) == -1)
	// 	return (-1);
	execve("/bin/cat", argv, NULL);
	return (0);
}

int	main(int argc, char *argv[])
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
				first_child(argv[1], argv[2], fds);
			else if (i == 1)
				last_child(argv[4], argv[3], fds);
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
