/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 23:52:33 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/25 00:01:42 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo_death(t_philo *philo)
{
	if (get_time() >= philo->time_to_die && philo->eating == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		messages(DIED, philo);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
}

static void	check_philo_meals(t_philo *philo)
{
	if (philo->eat_cont == philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finished++;
		philo->eat_cont++;
		pthread_mutex_unlock(&philo->data->lock);
	}
}

void	*death_checker(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		check_philo_death(philo);
		check_philo_meals(philo);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}
