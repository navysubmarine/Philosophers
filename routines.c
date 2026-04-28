/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:59:58 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/28 19:01:29 by marthoma         ###   ########.fr       */
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

static int	should_stop(t_global *g)
{
	pthread_mutex_lock(&(g->access_stop_var_mutex));
	if (g->stop)
	{
		pthread_mutex_unlock(&(g->access_stop_var_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(g->access_stop_var_mutex));
	return (0);
}

static int	check_philo_death(t_global *g, int i)
{
	long    current_time;

	pthread_mutex_lock(g->philo[i]->access_last_meal_time);
	if (g->philo[i]->last_meal_time == 0)
		return (pthread_mutex_unlock(g->philo[i]->access_last_meal_time), 0);
	current_time = getcurrenttime();
	if (current_time < 0)
		return (pthread_mutex_unlock(g->philo[i]->access_last_meal_time), -1);
	if ((current_time - g->philo[i]->last_meal_time) > g->time_to_die)
	{
		pthread_mutex_unlock(g->philo[i]->access_last_meal_time);
		pthread_mutex_lock(&(g->access_stop_var_mutex));
		g->stop = 1;
		pthread_mutex_unlock(&(g->access_stop_var_mutex));
		print_messages(DEAD, g->philo[i]->id, g->philo[i]);
		return (1);
	}
	pthread_mutex_unlock(g->philo[i]->access_last_meal_time);
	return (0);
}

static int	all_philos_done(t_global *g)
{
	pthread_mutex_lock(&(g->access_philos_done));
	if (g->philos_done == g->nb_of_philo)
	{
		pthread_mutex_lock(&(g->access_stop_var_mutex));
		g->stop = 1;
		pthread_mutex_unlock(&(g->access_stop_var_mutex));
		pthread_mutex_unlock(&(g->access_philos_done));
		return (1);
	}
	pthread_mutex_unlock(&(g->access_philos_done));
	return (0);
}

void	*routine_supervisor(void *data)
{
	int         i;
	t_global    *g;

	g = (t_global *)data;
	usleep(1000);
	while (1)
	{
		if (should_stop(g))
			return (NULL);
		i = 0;
		while (i < g->nb_of_philo)
		{
			if (check_philo_death(g, i) != 0)
				return (NULL);
			i++;
		}
		if (all_philos_done(g))
			return (NULL);
	}
	return (NULL);
}
