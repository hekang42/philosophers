/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 20:40:19 by hekang            #+#    #+#             */
/*   Updated: 2021/06/28 20:50:35 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_with_free(t_data *result)
{
	free(result);
	write(2, "Error: Wrong ARGS\n", 19);
	exit(1);
}

int		is_digit_string(char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
	{
		if (str[cnt] < '0' || str[cnt] > '9')
			return (0);
		cnt++;
	}
	return (1);
}
