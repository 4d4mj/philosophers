/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:59:50 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/25 00:02:12 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_end_checker(t_data *data, pthread_t *t0)
{
	pthread_mutex_lock(&data->lock);
	if (pthread_create(t0, NULL, &end_checker, &data->philos[0]))
		ft_error(NULL, data);
	pthread_mutex_unlock(&data->lock);
}

static void	start_philo_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_lock(&data->lock);
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			ft_error(NULL, data);
		pthread_mutex_unlock(&data->lock);
		ft_usleep(1);
	}
}

static void	join_philo_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			ft_error(NULL, data);
	}
}

int	init_thread(t_data *data)
{
	pthread_t	t0;

	data->start_time = get_time();
	if (data->meals_nb > 0)
		start_end_checker(data, &t0);
	start_philo_threads(data);
	join_philo_threads(data);
	if (data->meals_nb > 0)
	{
		if (pthread_join(t0, NULL))
			ft_error(NULL, data);
	}
	return (0);
}
