/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:42:16 by hahlee            #+#    #+#             */
/*   Updated: 2022/10/10 16:43:47 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_realloc(char **ptr, int cur_size, int add_size)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (cur_size + add_size + 1));
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, *ptr, cur_size + 1);
	free(*ptr);
	*ptr = tmp;
	return (0);
}
