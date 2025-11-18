/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:33 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/18 15:45:17 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	fill_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->n_philos];
		i++;
	}
}

int	init_philos_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (printf("Error: failed to malloc philosophers\n"), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (printf("Error: failed to malloc forks\n"), 1);
	}
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("Error: failed to init fork mutex\n"), 1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (printf("Error: failed to init print mutex\n"), 1);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->alive_mutex, NULL);
	fill_philo(data);
	data->start_time = current_time();
	return (0);
}
