/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:34:24 by hekang            #+#    #+#             */
/*   Updated: 2021/06/29 11:06:39 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long		get_time(void)
{
	unsigned long	result;
	struct timeval	current;

	gettimeofday(&current, NULL);
	result = current.tv_sec * 1000 + current.tv_usec / 1000;
	return (result);
}

unsigned long		calc_time(struct timeval time)
{
	unsigned long	result;

	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result);
}

int					eat_all(t_data *data)
{
	int				result;
	int				cnt;

	result = 0;
	cnt = -1;
	while (++cnt < data->input[number_of_philos])
	{
		usleep(1000);
		if (data->philo[cnt].eat_count < data->input[must_eat_count])
			return (0);
	}
	return (1);
}

void				*monitor(void *arg)
{
	t_philo			*philo;
	int				cnt;
	unsigned long	current;

	philo = (t_philo *)arg;
	while (1)
	{
		cnt = -1;
		while (++cnt < philo->data->input[number_of_philos])
		{
			current = get_time();
			if ((int)(current - calc_time(philo[cnt].last_eat_time)) >
				philo->data->input[time_to_die])
			{
				philo[cnt].data->end = 1;
				print_philo(philo, 4);
				return (0);
			}
			if (philo->data->input[must_eat_count] != -1)
				if (((philo[cnt].data->end) = (eat_all(philo->data))) == 1)
					return (0);
			usleep(100);
		}
	}
}
