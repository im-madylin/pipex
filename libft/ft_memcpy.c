/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:09:03 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/03 15:53:59 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sour;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = (unsigned char *)dst;
	sour = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest[i] = sour[i];
		i++;
	}
	return (dst);
}
