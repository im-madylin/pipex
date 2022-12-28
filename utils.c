/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:52:01 by hahlee            #+#    #+#             */
/*   Updated: 2022/12/28 17:02:21 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
