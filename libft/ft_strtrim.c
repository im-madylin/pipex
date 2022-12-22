/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:31:23 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/03 16:49:41 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	if (start >= len)
		return (ft_strdup(""));
	i = len - 1;
	while (ft_strchr(set, s1[i]))
		i--;
	end = i + 1;
	result = (char *)malloc(end - start + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 1);
	return (result);
}
