/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:50 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/17 16:03:19 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	is_alive(t_data *data)
{
	int	alive;

	pthread_mutex_lock(&data->alive_mutex);
	alive = data->all_alive;
	pthread_mutex_unlock(&data->alive_mutex);
	return (alive);
}

static void	eat(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	if (!is_alive(data))
		return ;
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("[%lld] Philosopher %d is eating\n",
		current_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!is_alive(data))
		return ;
	printf("[%lld] Philosopher %d is sleeping\n",
		current_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	usleep(data->time_to_sleep * 1000);
}

static void	think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!is_alive(data))
		return ;
	printf("[%lld] Philosopher %d is thinking\n",
		current_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&data->print_mutex);
		printf("[%lld] Philosopher %d has taken a fork\n",
			current_time() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		usleep(data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (1)
	{
		if (!is_alive(data))
			break ;
		eat(data, philo);
		ft_sleep(data, philo);
		think(data, philo);
	}
	return (NULL);
}
