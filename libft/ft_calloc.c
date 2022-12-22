/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:25:27 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/04 16:34:45 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	byte;

	byte = count * size;
	if (byte && (byte < count || byte < size))
		return (NULL);
	ptr = malloc(byte);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, byte);
	return (ptr);
}
