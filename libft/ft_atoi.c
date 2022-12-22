/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:38:08 by hahlee            #+#    #+#             */
/*   Updated: 2022/08/03 14:17:33 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	unsigned long long	max;
	int					sign;
	int					i;

	result = 0;
	max = 9223372036854775808ULL;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && result <= max)
		result = result * 10 + (str[i++] - '0');
	if (result >= max && sign == 1)
		return (-1);
	else if (result > max && sign == -1)
		return (0);
	return (result * sign);
}
