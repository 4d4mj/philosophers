/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 02:40:41 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/24 23:54:58 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*end_checker(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	pthread_mutex_lock(&philo->data->lock);
	if (pthread_create(&philo->t1, NULL, &death_checker, (void *)philo))
		return ((void *)1);
	pthread_mutex_unlock(&philo->data->lock);
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
		eat(philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}
