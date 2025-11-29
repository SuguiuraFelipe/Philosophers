/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:44 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/29 11:54:34 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	monitor_eat_enough(t_data *data)
{
	pthread_mutex_lock(&data->alive_mutex);
	data->all_alive = 0;
	pthread_mutex_unlock(&data->alive_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("[%lld] All philosophers have eaten enough\n",
		current_time() - data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
}

int	monitor_philo_died(t_data *data, int i, long long now)
{
	if ((now - data->philos[i].last_meal) >= data->time_to_die)
	{
		pthread_mutex_lock(&data->alive_mutex);
		data->all_alive = 0;
		pthread_mutex_unlock(&data->alive_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("[%lld] Philosopher %d died\n",
			now - data->start_time, data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

int	check_philosophers_status(t_data *data, int *all_full)
{
	int			i;
	long long	now;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		now = current_time();
		if (monitor_philo_died(data, i, now))
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (1);
		}
		if (data->must_eat_count != -1
			&& data->philos[i].meals_eaten < data->must_eat_count)
			*all_full = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		all_full;

	data = (t_data *)arg;
	while (1)
	{
		all_full = 1;
		if (check_philosophers_status(data, &all_full))
			return (NULL);
		if (data->must_eat_count != -1 && all_full)
		{
			monitor_eat_enough(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
