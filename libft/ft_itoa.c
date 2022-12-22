/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:08:26 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/03 15:00:37 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_count(long long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	else if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*result;
	long long	num;
	int			i;

	num = (long long)n;
	i = len_count(num);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	result[i--] = '\0';
	if (num < 0)
	{
		result[0] = '-';
		num *= -1;
	}
	else if (num == 0)
		result[i] = '0';
	while (num > 0)
	{
		result[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (result);
}
