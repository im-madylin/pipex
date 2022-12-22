/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:00:18 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/02 17:19:43 by hahlee           ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	char		result[11];
	long long	num;
	int			len;
	int			i;

	num = (long long)n;
	len = len_count(num);
	i = len - 1;
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
	write(fd, result, len);
}
