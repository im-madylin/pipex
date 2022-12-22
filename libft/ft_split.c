/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 21:56:12 by hahlee            #+#    #+#             */
/*   Updated: 2022/11/28 12:51:13 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			count++;
		}
		else
			s++;
	}
	return (count);
}

static int	input_word(char **result, char const *s, char c, int i)
{
	char const	*start;

	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s != c && *s)
				s++;
			result[i] = (char *)malloc(sizeof(char) * (s - start + 1));
			if (result[i] == NULL)
			{
				while (i >= 0)
					free(result[i--]);
				free(result);
				return (0);
			}
			ft_strlcpy(result[i++], start, s - start + 1);
		}
		else
			s++;
	}
	result[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;

	if (s == NULL)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	if (!input_word(result, s, c, i))
		return (NULL);
	return (result);
}
