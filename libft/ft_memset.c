/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:32:36 by hahlee            #+#    #+#             */
/*   Updated: 2022/07/15 14:51:27 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	ptr = (unsigned char *)b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ptr[i] = value;
		i++;
	}
	return (b);
}
