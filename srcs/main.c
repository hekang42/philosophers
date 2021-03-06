/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 11:28:06 by hekang            #+#    #+#             */
/*   Updated: 2021/06/29 11:25:22 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data			*get_data(char **argv)
{
	t_data		*result;
	int			cnt;

	result = (t_data *)malloc(sizeof(t_data));
	cnt = 0;
	while (argv[++cnt])
	{
		if (!is_digit_string(argv[cnt]) || !result)
			exit_with_free(result);
		result->input[cnt] = ft_atoi(argv[cnt]);
	}
	if (cnt != 6)
		result->input[cnt] = -1;
	result->end = 0;
	return (result);
}

int				init_philos(t_data *data)
{
	int			cnt;

	data->philo = (t_philo *)malloc(sizeof(t_philo) *
		data->input[number_of_philos]);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* data->input[number_of_philos]);
	cnt = -1;
	while (++cnt < data->input[number_of_philos])
	{
		pthread_mutex_init(&data->forks[cnt], NULL);
		if (cnt == 0)
			data->philo[cnt].left = &data->forks[
				data->input[number_of_philos] - 1];
		else
			data->philo[cnt].left = &data->forks[cnt - 1];
		data->philo[cnt].right = &data->forks[cnt];
		data->philo[cnt].data = data;
		data->philo[cnt].eat_count = 0;
		data->philo[cnt].dead = 0;
	}
	return (0);
}

void			create_philos(t_data *data)
{
	int			cnt;
	pthread_t	p;

	cnt = -1;
	gettimeofday(&data->start_time, NULL);
	while (++cnt < data->input[number_of_philos])
	{
		data->philo[cnt].n = cnt;
		data->philo[cnt].data = data;
		data->philo[cnt].last_eat_time = data->start_time;
		pthread_create(&data->philo[cnt].thread, NULL,
			philo, &data->philo[cnt]);
		pthread_detach(data->philo[cnt].thread);
	}
	pthread_create(&p, NULL, monitor, data->philo);
	pthread_join(p, NULL);
}

void			free_data(t_data *data)
{
	int			cnt;

	cnt = -1;
	while (++cnt < data->input[number_of_philos])
		pthread_mutex_destroy(&data->forks[cnt]);
	usleep(data->input[time_to_die] * 1000);
	free(data->forks);
	free(data->philo);
	free(data);
}

int				main(int argc, char **argv)
{
	t_data		*data;

	if (!(argc == 5) && !(argc == 6))
		return (0);
	data = get_data(argv);
	init_philos(data);
	create_philos(data);
	free_data(data);
	return (1);
}
