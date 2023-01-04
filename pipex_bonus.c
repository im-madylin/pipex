/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:53:53 by hahlee            #+#    #+#             */
/*   Updated: 2023/01/04 16:44:51 by hahlee           ###   ########.fr       */
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
	waitpid(pid, &last_status, 0);
	while (wait(&status) != -1)
		continue ;
	if (argvs.here_doc)
		unlink("temp");
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
		if (argc != 6)
			return (-1);
		argvs->cmd1 = 3;
		argvs->cmd_count = argc - 5;
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
		if (!ft_strncmp(tmp, limiter, ft_strlen(tmp) - 1))
		{
			safety_free(&tmp, 0);
			break ;
		}
		write(fd, tmp, ft_strlen(tmp));
		safety_free(&tmp, 0);
	}
	return (close(fd));
}
