/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:56 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/19 20:08:07 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long long	ft_atoll(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

int	is_alive(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->alive_mutex);
	res = data->all_alive;
	pthread_mutex_unlock(&data->alive_mutex);
	return (res);
}

void	smart_sleep(long long time, t_data *data)
{
	long long	start;

	start = current_time();
	while (is_alive(data) && (current_time() - start) < time)
		usleep(100);
}

void	print_msg(t_philo *p, t_data *d, char *msg)
{
	pthread_mutex_lock(&d->print_mutex);
	if (is_alive(d))
		printf("[%lld] Philosopher %d %s\n",
			current_time() - d->start_time, p->id, msg);
	pthread_mutex_unlock(&d->print_mutex);
}