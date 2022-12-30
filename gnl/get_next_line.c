/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:19:40 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/30 15:09:18 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	backup[BUFFER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	char		*result;
	int			check;

	result = NULL;
	check = backup_check(&result, backup);
	if (fd < 0 || BUFFER_SIZE < 0 || check == -1)
		return (NULL);
	else if (check == 1)
		return (result);
	while (1)
	{
		check = read_and_input(&result, buf, backup, fd);
		if (check == -1)
			return (NULL);
		else if (check == 0 || ft_indexof(result, '\n') != -1)
			break ;
	}
	return (result);
}

int	backup_check(char **result, char *backup)
{
	int	len;

	if (!ft_strlen(backup))
		return (0);
	len = ft_indexof(backup, '\n') + 1;
	if (len == 0)
		len = ft_strlen(backup);
	*result = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*result))
		return (-1);
	ft_strlcpy(*result, backup, len + 1);
	if (len < (int)ft_strlen(backup))
	{
		ft_strlcpy(backup, backup + len, ft_strlen(backup) - len + 1);
		return (1);
	}
	while (len)
		backup[--len] = 0;
	return (0);
}

int	read_and_input(char **result, char *buf, char *backup, int fd)
{
	int	read_len;
	int	newline_i;

	read_len = read(fd, buf, BUFFER_SIZE);
	if (read_len <= 0)
	{
		if (read_len < 0 || !result)
		{
			safer_free(result);
			return (-1);
		}
		return (0);
	}
	buf[read_len] = '\0';
	newline_i = ft_indexof(buf, '\n') + 1;
	if (newline_i != 0 && newline_i < read_len)
	{
		if (!input_data(result, buf, newline_i))
			return (-1);
		ft_strlcpy(backup, buf + newline_i, read_len - newline_i + 1);
	}
	else
		if (!input_data(result, buf, read_len))
			return (-1);
	return (1);
}

int	input_data(char **result, char *buf, int size)
{
	int	result_len;

	if (*result)
	{
		result_len = ft_strlen(*result);
		if (ft_realloc(result, result_len, size) == -1)
		{
			safer_free(result);
			return (0);
		}
		ft_strlcpy(*result + result_len, buf, size + 1);
	}
	else
	{
		*result = (char *)malloc(sizeof(char) * (size + 1));
		if (!(*result))
			return (0);
		ft_strlcpy(*result, buf, size + 1);
	}
	return (1);
}
