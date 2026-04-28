/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:59:58 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 19:04:00 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->g->ok_init_mutex));
	pthread_mutex_unlock(&(philo->g->ok_init_mutex));
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->access_last_meal_time);
	philo->last_meal_time = getcurrenttime();
	if (philo->last_meal_time < 0)
		return (pthread_mutex_unlock(philo->access_last_meal_time), 1);
	pthread_mutex_unlock(philo->access_last_meal_time);
	if (!philo->last_meal_time)
		return (1);
	return (0);
}

static void	*routine_limited(t_philo *philo)
{
	while (philo->times_ive_eaten < philo->g->max_eat)
	{
		if (think(philo) || eat(philo))
			return (NULL);
		philo->times_ive_eaten++;
		if (philo->times_ive_eaten == philo->g->max_eat)
		{
			pthread_mutex_lock(&(philo->g->access_philos_done));
			philo->g->philos_done++;
			pthread_mutex_unlock(&(philo->g->access_philos_done));
			return (NULL);
		}
		if (my_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (init_philo_routine(philo))
		return (NULL);
	if (philo->g->max_eat > 0)
		return (routine_limited(philo));
	while (1)
	{
		if (think(philo) || eat(philo) || my_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

void	*routine_solo_philo(void *data)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)data;
	pthread_mutex_lock(&(philo->g->ok_init_mutex));
	pthread_mutex_unlock(&(philo->g->ok_init_mutex));
	if (print_messages(THINKING, philo->id, philo))
		return (NULL);
	current_time = getcurrenttime();
	if (current_time < 0)
		return (NULL);
	usleep(philo->time_to_die * 1000);
	print_messages(DEAD, philo->id, philo);
	return (NULL);
}
