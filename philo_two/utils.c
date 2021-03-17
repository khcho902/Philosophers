/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:28:01 by kycho             #+#    #+#             */
/*   Updated: 2021/03/17 12:48:51 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long			gettimeofday_by_millisec(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int				ft_atoi(const char *str)
{
	size_t	i;
	int		res;
	int		sign;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	i += (str[i] == '-' || str[i] == '+') ? 1 : 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (sign * res);
}

void			less_error_msleep(long milliseconds)
{
	long	base_time;

	base_time = gettimeofday_by_millisec();
	while (TRUE)
	{
		if (milliseconds <= gettimeofday_by_millisec() - base_time)
			return ;
		usleep(100);
	}
}

static size_t	get_n_len(int n)
{
	size_t len;
	size_t minus;

	if (n == 0)
		return (1);
	minus = (n < 0) ? 1 : 0;
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (minus + len);
}

char			*ft_itoa(int n)
{
	char	*res;
	size_t	len;

	len = get_n_len(n);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[0] = (n < 0) ? '-' : '0';
	res[len] = '\0';
	len--;
	while (n != 0)
	{
		res[len] = (n % 10 < 0) ? -1 * (n % 10) + '0' : (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (res);
}
