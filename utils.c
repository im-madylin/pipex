/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:52:01 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 18:44:59 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(int code, char *name)
{
	ft_puterror("pipex: ");
	ft_puterror(name);
	ft_puterror(": ");
	if (code == 127)
	{
		ft_puterror("command not found\n");
		exit(127);
	}
	else if (code == 1)
	{
		ft_puterror("No such file or directory\n");
		exit(1);
	}
}

void	ft_puterror(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
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
