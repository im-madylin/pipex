/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:49:32 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/26 20:15:05 by hahlee           ###   ########.fr       */
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

void	first_child(char *file, char *com, int fds[], char *envp[]);
void	last_child(char *file, char *com, int fds[], char *envp[]);
char	**split_envp(char *envp[]);
int		safety_free(char *str, int result);
int		double_free(char **str, int result);
int		check_command(char *com, char *envp[], char **result);

#endif