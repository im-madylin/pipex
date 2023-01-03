/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_to_execve_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:41:11 by hahlee            #+#    #+#             */
/*   Updated: 2023/01/03 14:07:21 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**split_com(char *com)
{
	char	**result;
	char	*start;
	char	*end;
	int		i;

	result = ft_split(com, ' ');
	if (result == NULL)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i][0] == '\'' || result[i][0] == '\"')
		{
			start = ft_strnstr(com, result[i], -1) + 1;
			end = com + (ft_strlen(com) - 1);
			result[i] = ft_substr(com, start - com, end - start);
			if (result[i++] == NULL)
				return (double_free(&result, 0), NULL);
			while (result[i])
				safety_free(&(result[i++]), 0);
			break ;
		}
		i++;
	}
	return (result);
}

int	check_command(char *com, char *envp[], char **result)
{
	char	**path;
	char	*temp;
	int		check;

	if (com == NULL)
		exit_error(127, "");
	if (access(com, X_OK) == 0)
	{
		*result = com;
		return (1);
	}
	path = split_envp(envp);
	if (path == NULL)
		return (-1);
	temp = ft_strjoin("/", com);
	if (temp == NULL)
		return (double_free(&path, -1));
	check = combining_path(path, temp, result);
	return (double_free(&path, check), safety_free(&temp, check));
}

int	combining_path(char **path, char *com, char **result)
{
	int	i;

	i = 0;
	while (path[i])
	{
		*result = ft_strjoin(path[i], com);
		if (*result == NULL)
			return (-1);
		if (access(*result, X_OK) == 0)
			return (1);
		safety_free(result, 0);
		i++;
	}
	return (0);
}

char	**split_envp(char *envp[])
{
	char	**path;
	char	*temp;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		temp = ft_strnstr(envp[i], "PATH=", -1);
		if (temp != NULL)
		{
			path = ft_split(temp + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}
