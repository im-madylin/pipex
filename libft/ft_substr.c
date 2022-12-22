/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:42:20 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/02 20:28:11 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start || !len)
		return (ft_strdup(""));
	if (s_len - start < len)
		result = (char *)malloc(s_len - start + 1);
	else
		result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, &s[start], len + 1);
	return (result);
}
