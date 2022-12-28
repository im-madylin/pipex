/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:52:01 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 15:12:44 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_command(char *com, char *envp[], char **result)
{
	char	**path;
	char	*temp;
	int		i;

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
	i = 0;
	while(path[i])
	{
		*result = ft_strjoin(path[i], temp);
		if (*result == NULL)
			return (double_free(&path, -1), safety_free(&temp, -1));
		if (access(*result, X_OK) == 0)
			return (double_free(&path, 1), safety_free(&temp, 1));
		safety_free(result, 0);
		i++;
	}
	return (double_free(&path, 0), safety_free(&temp, 0));
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

char	**split_com(char *com)
{
	char	**result;
	char	*start;
	char	*end;
	int		i;
	int		temp;

	result = ft_split(com, ' ');
	if (result == NULL)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i][0] == '\'')
		{
			temp = i;
			start = ft_strnstr(com, result[i], -1) + 1;
			while (result[i])
			{
				safety_free(&(result[i]), 0);
				i++;
			}
			end = com + (ft_strlen(com) - 1);
			result[temp] = ft_substr(com, start - com, end - start);
			if (result[temp] == NULL)
				return (double_free(&result, 0), NULL);
			break;
		}
		i++;
	}
	return (result);
}

void	exit_127(void)
{
	const char	*str = "command not found\n";
	
	write(2, str, ft_strlen(str));
	exit(127);
}

int	double_free(char ***str, int result)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
	return (result);
}

int	safety_free(char **str, int result)
{
	free(*str);
	*str = NULL;
	return (result);
}