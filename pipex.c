/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:50:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/19 17:11:35 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
	}
	else if (pid == 0)
	{
		fd = open(argv[1], O_RDWR | O_CREAT, 0644);
		if (fd == -1)
			return (0);
		dup2(fd, 0);
		dup2(fds[WRITE], 1);
	}
	else
		return (0);
	return (0);
}
