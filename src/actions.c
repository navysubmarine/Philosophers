/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:59:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 11:42:34 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	think(t_philo *philo)
{
	if (print_messages(THINKING, philo->id, philo))
		return (1);
	//usleep(100);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		if (print_messages(TOOK_FORK, philo->id, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pthread_mutex_lock(philo->left_fork);
		if (print_messages(TOOK_FORK, philo->id, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_messages(TOOK_FORK, philo->id, philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		if (print_messages(TOOK_FORK, philo->id, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo) || print_messages(EATING, philo->id, philo))
	{
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
	pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
	if (philo->g->stop)
	{
		pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
	return (0);
}

int	my_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
	if (philo->g->stop)
	{
		pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
	print_messages(SLEEPING, philo->id, philo);
	usleep(philo->time_to_sleep / 1000);
	pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
	if (philo->g->stop)
	{
		pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
	return (0);
}
