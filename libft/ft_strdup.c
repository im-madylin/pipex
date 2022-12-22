/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:48:54 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/02 20:25:23 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len;

	len = ft_strlen(s1) + 1;
	ptr = (char *)malloc(len);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, len);
	return (ptr);
}
