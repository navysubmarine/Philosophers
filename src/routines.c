/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:59:58 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/27 16:44:47 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->g->stop)
		return (NULL);
	pthread_mutex_lock(&(philo->g->ok_init_mutex));
	pthread_mutex_unlock(&(philo->g->ok_init_mutex));
	pthread_mutex_lock(philo->access_last_meal_time);
	philo->last_meal_time = getcurrenttime();
	if (philo->last_meal_time < 0)
		return (NULL);
	pthread_mutex_unlock(philo->access_last_meal_time);
	if (!philo->last_meal_time)
		return (NULL);
	if (philo->g->max_eat > 0)
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
	else
	{
		while (1)
		{
			if (think(philo) || eat(philo) || my_sleep(philo))
				return (NULL);
		}
	}
	return (NULL);
}

void	*routine_solo_philo(void *data)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)data;
	think(philo);
	current_time = getcurrenttime();
	if (current_time < 0)
		return (NULL);
	print_messages(4, philo->id, philo);
	return (NULL);
}

void	*routine_supervisor(void *data)
{
	int			i;
	t_global	*g;
	long		current_time;

	i = 0;
	g = (t_global *)data;
	usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&(g->access_stop_var_mutex));
		if (g->stop)
		{
			pthread_mutex_unlock(&(g->access_stop_var_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(g->access_stop_var_mutex));
		while (i < g->nb_of_philo)
		{
			pthread_mutex_lock(g->philo[i]->access_last_meal_time);
			current_time = getcurrenttime();
			if (current_time < 0)
				return (NULL);
			if ((current_time - g->philo[i]->last_meal_time) > g->time_to_die)
			{
				pthread_mutex_unlock(g->philo[i]->access_last_meal_time);
				pthread_mutex_lock(&(g->access_stop_var_mutex));
				g->stop = 1;
				pthread_mutex_unlock(&(g->access_stop_var_mutex));
				print_messages(4, g->philo[i]->id, g->philo[i]);
				return (NULL);
			}
			pthread_mutex_unlock(g->philo[i]->access_last_meal_time);
			pthread_mutex_lock(&(g->access_philos_done));
			if (g->philos_done == g->nb_of_philo)
			{
				pthread_mutex_lock(&(g->access_stop_var_mutex));
				g->stop = 1;
				pthread_mutex_unlock(&(g->access_stop_var_mutex));
				pthread_mutex_unlock(&(g->access_philos_done));
				return (NULL);
			}
			pthread_mutex_unlock(&(g->access_philos_done));
			i++;
		}
		i = 0;
	}
	return (NULL);
}
