/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:49:32 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 16:54:36 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1

/* pipex.c */
int		fork_child(int argc, char *argv[], char *envp[], int fds[]);
void	first_child(char *file, char *com, int fds[], char *envp[]);
void	last_child(char *file, char *com, int fds[], char *envp[]);

/* ready_to_execve.c */
char	**split_com(char *com);
int		check_command(char *com, char *envp[], char **result);
int		combining_path(char **path, char *com, char **result);
char	**split_envp(char *envp[]);

/* utils.c */
void	exit_127(void);
int		double_free(char ***str, int result);
int		safety_free(char **str, int result);

#endif