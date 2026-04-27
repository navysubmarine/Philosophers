/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/27 14:49:09 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!philo->start)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&(philo->g->access_last_meal_time));
	philo->last_meal_time = getcurrenttime();
	pthread_mutex_unlock(&(philo->g->access_last_meal_time));
	if (!philo->last_meal_time)
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

void	*routine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&(philo->g->ok_init_mutex));
	pthread_mutex_unlock(&(philo->g->ok_init_mutex));
	pthread_mutex_lock(&(philo->g->access_last_meal_time));
	philo->last_meal_time = getcurrenttime();
	pthread_mutex_unlock(&(philo->g->access_last_meal_time));
	if (!philo->last_meal_time)
		return (NULL);
	philo->start = philo->last_meal_time;
	if (philo->g->stop)
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
				pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
				philo->g->philos_done++;
				if (philo->g->philos_done == (int)philo->g->nb_of_philo)
					philo->g->stop = 1;
				pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
				return (NULL);
			}
			if (my_sleep(philo))
				return (NULL);
		}
		pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
		philo->g->philos_done++;
		if (philo->g->philos_done == philo->g->nb_of_philo)
			philo->g->stop = 1;
		pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
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
	if (!current_time)
		return (NULL);
	print_messages(4, philo->id, philo);
	return (NULL);
}

void	*routine_supervisor(void *data)
{
	int			i;
	t_global	*g;

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
			pthread_mutex_lock(&(g->access_last_meal_time));
			if ((getcurrenttime()
					- g->philo[i]->last_meal_time) > g->time_to_die)
			{
				pthread_mutex_unlock(&(g->access_last_meal_time));
				pthread_mutex_lock(&(g->access_stop_var_mutex));
				g->stop = 1;
				pthread_mutex_unlock(&(g->access_stop_var_mutex));
				print_messages(4, g->philo[i]->id, g->philo[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&(g->access_last_meal_time));
			i++;
		}
		i = 0;
	}
	return (NULL);
}

int	init_threads(t_global *g, t_philo **philo, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&(g->ok_init_mutex));
	if (nb_of_philo == 1)
	{
		if (pthread_create(&(philo[0]->th), NULL, &routine_solo_philo,
				philo[0]) != 0)
		{
			free_global(g);
			printf("Error: thread creation failed\n");
			return (1);
		}
	}
	else
	{
		while (i < nb_of_philo)
		{
			if (pthread_create(&(philo[i]->th), NULL, &routine_philo,
					philo[i]) != 0)
			{
				free_global(g);
				printf("Error: thread creation failed\n");
				return (1);
			}
			// printf("Thread %d a ete cree\n", i + 1);
			i++;
		}
	}
	g->simulation_start = getcurrenttime();
	if (!g->simulation_start)
	{
		free_global(g);
		return (1);
	}
	pthread_mutex_unlock(&(g->ok_init_mutex));
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(philo[i]->th, NULL) != 0)
		{
			free_global(g);
			printf("Error: philo threads haven't been joined\n");
			return (1);
		}
		// printf("Thread %d has finished execution\n", i + 1);
		i++;
	}
	if (pthread_join(g->supervisor, NULL) != 0)
	{
		free_global(g);
		printf("Error: supervisor thread hasn't been joined\n");
		return (1);
	}
	return (0);
}

int	init_supervisor(t_global *g)
{
	if (pthread_create(&g->supervisor, NULL, &routine_supervisor, g) != 0)
	{
		free_global(g);
		printf("Error: supervisor thread creation failed\n");
		return (1);
	}
	// printf("Supervisor a ete cree\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (check_arg(argc, argv))
		return (1);
	if (init(&g, argc, argv))
		return (1);
	free_global(&g);
	return (0);
}
