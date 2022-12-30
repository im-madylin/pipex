/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:15:22 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/30 15:14:23 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

# define READ 0
# define WRITE 1
# define NEW 0
# define OLD 1

typedef struct s_argvs
{
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd1;
	int		here_doc;
}	t_argvs;



/* main.c */
int		fork_child(t_argvs argvs);
void	first_child(t_argvs argvs, int fds[]);
void	middle_child(t_argvs argvs, int fds[][2], int index);
void	last_child(t_argvs argvs, int fds[]);
int		get_here_doc(char *limiter);

/* ready_to_execve.c */
char	**split_com(char *com);
int		check_command(char *com, char *envp[], char **result);
int		combining_path(char **path, char *com, char **result);
char	**split_envp(char *envp[]);

/* utils.c */
void	exit_error(int code, char *name);
void	ft_puterror(char *str);
int		double_free(char ***str, int result);
int		safety_free(char **str, int result);

#endif