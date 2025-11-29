/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:50 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/19 20:07:55 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	take_forks(t_philo *p, t_data *d)
{
	if (p->id % 2 == 0)
		usleep(500);
	pthread_mutex_lock(p->left_fork);
	print_msg(p, d, "has taken a fork");
	pthread_mutex_lock(p->right_fork);
	print_msg(p, d, "has taken a fork");
}

static void	eat(t_philo *p, t_data *d)
{
	take_forks(p, d);
	pthread_mutex_lock(&d->meal_mutex);
	p->last_meal = current_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&d->meal_mutex);
	print_msg(p, d, "is eating");
	smart_sleep(d->time_to_eat, d);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

static void	ph_sleep(t_philo *p, t_data *d)
{
	print_msg(p, d, "is sleeping");
	smart_sleep(d->time_to_sleep, d);
}

static void	run_cycle(t_philo *p, t_data *d)
{
	while (is_alive(d))
	{
		eat(p, d);
		if (!is_alive(d))
			return ;
		ph_sleep(p, d);
		if (!is_alive(d))
			return ;
		print_msg(p, d, "is thinking");
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)arg;
	d = p->data;
	if (d->n_philos == 1)
	{
		pthread_mutex_lock(p->left_fork);
		print_msg(p, d, "has taken a fork");
		usleep(d->time_to_die * 1000);
		pthread_mutex_unlock(p->left_fork);
		return (NULL);
	}
	run_cycle(p, d);
	return (NULL);
}
