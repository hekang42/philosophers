/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:45:02 by hekang            #+#    #+#             */
/*   Updated: 2021/06/29 13:04:35 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				print_philo(t_philo *philo, int type)
{
	unsigned long	time;
	uint64_t		sec;
	struct timeval	current;

	gettimeofday(&current, NULL);
	sec = current.tv_sec - philo->data->start_time.tv_sec;
	time = sec * 1000 + (current.tv_usec - philo->data->start_time.tv_usec)
		/ 1000;
	if (type == 0 && !philo->data->end)
		printf("[%lu ms] %d has taken a fork\n", time, philo->n + 1);
	else if (type == 1 && !philo->data->end)
		printf("[%lu ms] %d is eating\n", time, philo->n + 1);
	else if (type == 2 && !philo->data->end)
		printf("[%lu ms] %d is sleeping\n", time, philo->n + 1);
	else if (type == 3 && !philo->data->end)
		printf("[%lu ms] %d is thinking\n", time, philo->n + 1);
	else if (type == 4)
		printf("[%lu ms] %d died\n", time, philo->n + 1);
}

void				eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	print_philo(philo, 0);
	print_philo(philo, 0);
	print_philo(philo, 1);
	gettimeofday(&philo->last_eat_time, NULL);
	usleep(philo->data->input[time_to_eat] * 1000);
	++philo->eat_count;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void				sleeping(t_philo *philo)
{
	print_philo(philo, 2);
	usleep(philo->data->input[time_to_sleep] * 1000);
}

void				thinking(t_philo *philo)
{
	print_philo(philo, 3);
}

void				*philo(void *argv)
{
	t_philo			*philo;

	philo = argv;
	if (philo->n % 2)
		usleep(philo->data->input[time_to_eat] * 500);
	while (!philo->dead && !philo->data->end)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		usleep(100);
	}
	return (0);
}
