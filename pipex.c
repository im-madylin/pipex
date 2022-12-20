/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/20 16:24:47 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h> //

int	check_command(char *com)
{
	//access로 커맨드 정상여부 확인
	//$PATH의 경로를 추출해오는 방법 확인해서, 콜론을 기준으로 쪼개 명령어 앞에 붙이고 access 검증
}

int	first_child(char *file, char *com, int fds[])
{
	int	fd;

	close(fds[READ]);
	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, 0);
	close(fd);
	dup2(fds[WRITE], 1);
	close(fds[WRITE]);
	if (check_command(com) == -1)
		return (-1);
	exceve();
	return (0);
}

int	middle_child(char *com, int fds[])
{
	dup2(fds[READ], 0);
	close(fds[READ]);
	dup2(fds[WRITE], 1);
	close(fds[WRITE]);
	if (check_command(com) == -1)
		return (-1);
	exceve();
	return (0);
}

int	last_child(char *file, char *com, int fds[])
{
	int	fd;

	close(fds[WRITE]);
	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	dup2(fd, 1);
	close(fd);
	dup2(fds[READ], 0);
	close(fds[READ]);
	if (check_command(com) == -1)
		return (-1);
	exceve();
	return (0);
}

int	main(int argc, char *argv[])
{
	int		fds[2];
	int		fd;
	pid_t	pid;
	int		status;

	if (argc != 5)
		return (0);
	if (pipe(fds) == -1)
		return (0);
	pid = 1;
	if (pid > 0)
	{
		//부모 프로세스
	}
	else if (pid == 0)
	{
		//자식 프로세스
	}
	else
		return (0);
	return (0);
}
