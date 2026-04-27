/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:59:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/27 15:49:52 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	think(t_philo *philo)
{
	if (philo->g->stop)
		return (1);
	print_messages(1, philo->id, philo);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->g->stop)
		return (1);
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		print_messages(5, philo->id, philo);
		pthread_mutex_lock(philo->left_fork);
		print_messages(5, philo->id, philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_messages(5, philo->id, philo);
		pthread_mutex_lock(philo->right_fork);
		print_messages(5, philo->id, philo);
	}
	if (philo->g->stop)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	print_messages(2, philo->id, philo);
	philo->start = getcurrenttime();
	if (philo->start < 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->access_last_meal_time);
	philo->last_meal_time = getcurrenttime();
	pthread_mutex_unlock(philo->access_last_meal_time);
	if (philo->last_meal_time < 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->g->stop)
		return (1);
	return (0);
}

int	my_sleep(t_philo *philo)
{
	if (philo->g->stop)
		return (1);
	print_messages(3, philo->id, philo);
	if (philo->g->stop)
		return (1);
	usleep(philo->time_to_sleep / 2 * 1000);
	if (philo->g->stop)
		return (1);
	usleep(philo->time_to_sleep / 2 * 1000);
	if (philo->g->stop)
		return (1);
	return (0);
}
