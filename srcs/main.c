/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 11:28:06 by hekang            #+#    #+#             */
/*   Updated: 2021/06/28 14:30:45 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread(void *vargp);

void			exit_with_free(t_data *result)
{
	free(result);
	write(2, "Error: Wrong ARGS\n", 19);
	exit(1);
}

int				is_digit_string(char *str)
{
	int			cnt;

	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt] < '0' || str[cnt] > '9')
			return (0);
		cnt++;
	}
	return (1);
}

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
	return (result);
}

int				init_philos(t_data *data)
{
	int			cnt;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->input[number_of_philos]);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* data->input[number_of_philos]);
	cnt = -1;
	while (++cnt < data->input[number_of_philos])
	{
		pthread_mutex_init(&data->forks[cnt], NULL);
		if (cnt == 0)
			data->philo[cnt].left = &data->forks[data->input[number_of_philos] - 1];
		else
			data->philo[cnt].left = &data->forks[cnt - 1];
		data->philo[cnt].right = &data->forks[cnt];
		data->philo[cnt].data = data;
		// pthread_create(&philos[cnt].thread, NULL, t_function, )
	}
	return (0);
}

void			create_philos(t_data *data)
{
	int			cnt;

	cnt = -1;
	gettimeofday(&data->start_time, NULL);
	while (++cnt < data->input[number_of_philos])
	{
		if (cnt % 2)
			usleep(1000);
		data->philo[cnt].n = cnt;
		data->philo[cnt].last_eat_time = data->start_time;
		pthread_create(&data->philo[cnt].thread, NULL, philo, &data->philo[cnt]);
	}
}

int				main(int argc, char **argv)                                  /* 메인 스레드가 시작되었다 */
{
	t_data		*data;
	
	if (!(argc == 5) && !(argc == 6))
		return (0);
	data = get_data(argv);
	init_philos(data);
	create_philos(data);
	while (1);
	return (1);
}