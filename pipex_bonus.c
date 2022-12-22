/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:53 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/22 21:11:43 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	middle_child(char *com, int fds[])
{
	dup2(fds[READ], 0);
	close(fds[READ]);
	dup2(fds[WRITE], 1);
	close(fds[WRITE]);
	if (check_command(com) == -1)
		return (-1);
	//execve();
	return (0);
}

int	main(int argc, char *argv[])
{
	int		fds[2];
	pid_t	pid;
	//int		status;
	int		i;

	(void)argv;

	if (argc < 5)
		return (0);
	i = 0;
	while (i < argc - 3)
	{
		pid = fork();
		if (pipe(fds) == -1) //수정해야함
			return (0);
		if (pid > 0)
		{
			printf("parents %d, %d\n", pid, i);
		}
		else if (pid == 0)
		{
			printf("child %d\n", i);
			if (i == 0)
				first_child(argv[1], argv[2], fds);
			else if (i == argc - 4)
				last_child(argv[argc - 1], argv[argc - 2], fds);
			break ;
		}
		else
			return (0);
		i++;
	}
	//wait(&status);
	return (0);
}
