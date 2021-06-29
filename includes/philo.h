/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 14:11:33 by hekang            #+#    #+#             */
/*   Updated: 2021/06/29 09:48:05 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

enum					e_philo
{
	number_of_philos = 1,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	must_eat_count
};

typedef struct			s_data
{
	int					input[6];
	struct timeval		start_time;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		msg;
	int					end;
}						t_data;

struct					s_philo
{
	int					n;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t			thread;
	struct timeval		last_eat_time;
	t_data				*data;
	int					eat_count;
	int					dead;
};

int						ft_atoi(const char *str);
void					*philo(void *argv);
void					*monitor(void *arg);
void					print_philo(t_philo *philo, int type);
void					exit_with_free(t_data *result);
int						is_digit_string(char *str);

#endif
