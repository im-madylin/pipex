/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 19:35:50 by hahlee            #+#    #+#             */
/*   Updated: 2022/07/18 21:10:35 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*p1 = (const unsigned char *)s1;
	const unsigned char	*p2 = (const unsigned char *)s2;

	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i] || p1[i] == '\0' || p2[i] == '\0')
		{
			if (127 < p1[i] - p2[i])
			{
				return (p1[i] - p2[i] - 127);
			}
			else
				return (p1[i] - p2[i]);
		}
		i++;
	}
	return (0);
}
