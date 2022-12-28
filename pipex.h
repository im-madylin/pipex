/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:49:32 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 15:44:23 by hahlee           ###   ########.fr       */
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
int 	fork_child(int argc, char *argv[], char *envp[], int fds[]);
void	first_child(char *file, char *com, int fds[], char *envp[]);
void	last_child(char *file, char *com, int fds[], char *envp[]);

/* utils.c */
char	**split_envp(char *envp[]);
char	**split_com(char *com);
int		safety_free(char **str, int result);
int		double_free(char ***str, int result);
int		check_command(char *com, char *envp[], char **result);
void	exit_127(void);

#endif