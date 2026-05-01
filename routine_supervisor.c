/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_supervisor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:03:35 by marthoma          #+#    #+#             */
/*   Updated: 2026/05/01 11:06:14 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop_simulation(t_global *g)
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
	long	current_time;

	pthread_mutex_lock(g->philo[i]->access_last_meal_time);
	if (g->philo[i]->last_meal_time == 0)
		return (pthread_mutex_unlock(g->philo[i]->access_last_meal_time), 0);
	current_time = getcurrenttime();
	/*TODO: this information does not propagate*/
	if (current_time < 0)
		return (pthread_mutex_unlock(g->philo[i]->access_last_meal_time), -1);
	if ((current_time - g->philo[i]->last_meal_time) >= g->time_to_die)
	{
		pthread_mutex_unlock(g->philo[i]->access_last_meal_time);
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
	int			i;
	t_global	*g;

	g = (t_global *)data;
	pthread_mutex_lock(&(g->ok_init_mutex));
	pthread_mutex_unlock(&(g->ok_init_mutex));
	while (1)
	{
		usleep(1000);
		if (should_stop_simulation(g))
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
