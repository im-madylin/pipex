/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:15:22 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/29 12:55:11 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1
# define NEW 0
# define OLD 1

/* pipex.c */
int		fork_child(int argc, char *argv[], char *envp[]);
void	first_child(char *file, char *com, int fds[], char *envp[]);
void	middle_child(char *com, int fds[][2], char *envp[]);
void	last_child(char *file, char *com, int fds[], char *envp[]);

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