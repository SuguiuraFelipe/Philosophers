/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:50:39 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/17 16:10:39 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	init_data(t_data *data)
{
	data->n_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->must_eat_count = -1;
	data->all_alive = 1;
	data->forks = NULL;
	data->philos = NULL;
	data->start_time = 0;
	return (0);
}

static int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: invalid arguments.\n"), 1);
	data->n_philos = ft_atoll(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoll(argv[5]);
	if (data->n_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat_count <= 0))
		return (printf("Error: invalid arguments.\n"), 1);
	data->all_alive = 1;
	data->start_time = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	init_data(&data);
	if (parse_args(&data, argc, argv))
		return (1);
	if (init_philos_mutex(&data))
		return (1);
	if (start_threads(&data))
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor_death, &data))
		return (printf("Error: failed to create monitor thread\n"), 1);
	if (join_threads(&data))
		return (1);
	if (pthread_join(monitor_thread, NULL))
		return (1);
	clean_all(&data);
	return (0);
}
