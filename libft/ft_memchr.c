/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:12:34 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/03 15:48:36 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	value;
	size_t			i;

	src = (unsigned char *)s;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == value)
			return (&src[i]);
		i++;
	}
	if (i < n && c == '\0')
		return (&src[i]);
	return (0);
}
