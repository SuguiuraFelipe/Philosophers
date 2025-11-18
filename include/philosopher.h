/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:49:44 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/11/17 16:10:44 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal;
	int				meals_eaten;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				n_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat_count;
	int				all_alive;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	alive_mutex;
	t_philo			*philos;
	long long		start_time;
}					t_data;

long long			ft_atoll(const char *str);
int					init_philos_mutex(t_data *data);
int					start_threads(t_data *data);
int					join_threads(t_data *data);
long long			current_time(void);
void				*philo_routine(void *arg);
void				*monitor_death(void *arg);
int					monitor_philo_died(t_data *data, int i, long long now);
void				clean_all(t_data *data);

#endif
