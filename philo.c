/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/23 18:22:30 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getcurrenttime(void)
{
	struct timeval	time;
	long			value;

	if (gettimeofday(&time, NULL))
		return (-1);
	else
	{
		value = (long)time.tv_sec * 1000 + (long)time.tv_usec / 1000;
		return (value);
	}
}

int	think(t_philo *philo)
{
	if(philo->g->stop)
		return (1);
	printf("%sID: %d - I am thinking%s\n", GREEN, philo->id, NC);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->g->stop)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	philo->end = getcurrenttime();
	if (!philo->end)
		return (1);
	if (philo->g->stop)
		return (1);
	printf("%sID: %d - I am eating%s\n", YELLOW, philo->id, NC);
	philo->start = getcurrenttime();
	if (!philo->start)
		return (1);
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
	printf("%sID: %d - I am sleeping%s\n", BLUE, philo->id, NC);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

void	*routine_philo(void *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)data;
	pthread_mutex_lock(philo->g->ok_init_mutex);
	pthread_mutex_unlock(philo->g->ok_init_mutex);
	philo->end = getcurrenttime();
	if (!philo->end)
		return (NULL);
	philo->start = philo->end;
	if (philo->g->stop)
		return (NULL);
	while (1)
	{
		think(philo);
		if (eat(philo))
			return (NULL);
		my_sleep(philo);
		i++;
	}
	return (NULL);
}

void	*routine_supervisor(void *data)
{
	unsigned int i;
	t_global *g;

	i = 0;
	g = (t_global *)data;
	while (1)
	{
		while (i < g->nb_of_philo)
		{
			if((g->philo[i]->end - g->philo[i]->start) > g->time_to_die)
			{
				g->stop = 1;
				printf("%sPhilo %d is dead %s\n", PURPLE, g->philo[i]->id, NC);
				return (NULL);
			}	
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
	pthread_mutex_lock(g->ok_init_mutex);
	while (i < nb_of_philo)
	{
		if (pthread_create(&(philo[i]->th), NULL, &routine_philo, philo[i]) != 0)
		{
			free_global(g);
			printf("Error: thread creation failed\n");
			return (1);
		}
		printf("Thread %d a ete cree\n", i + 1);
		i++;
	}
	pthread_mutex_unlock(g->ok_init_mutex);
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(philo[i]->th, NULL) != 0)
		{
			free_global(g);
			printf("Error: thread haven't been joined\n");
			return (1);
		}
		printf("Thread %d has finished execution\n", i + 1);
		i++;
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
	printf("Supervisor a ete cree\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_global	g;

	if (check_arg(argc, argv))
		return (1);
	if (init(&g, argc, argv))
		return (1);
	return (0);
}
