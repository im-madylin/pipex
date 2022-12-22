/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:23:52 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/03 16:16:44 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*sour;
	size_t			i;

	dest = (unsigned char *)dst;
	sour = (unsigned char *)src;
	if (dst == src || len == 0)
		return (dst);
	if (dst < src)
	{
		i = 0;
		while (len--)
		{
			dest[i] = sour[i];
			i++;
		}
		return (dst);
	}
	i = len - 1;
	while (len--)
	{
		dest[i] = sour[i];
		i--;
	}
	return (dst);
}
