/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:31:58 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/29 15:00:12 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	should_stop(t_philo *philo, int code)
{
	pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
	if (philo->g->stop && code != DEAD)
	{
		pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
	return (0);
}

static void	print_line(int code, unsigned int id, t_philo *philo)
{
	long	t;
	long ts;

	ts = getcurrenttime();
	if (ts < 0)
		return ;
	t = ts - philo->g->simulation_start;
	if (code == THINKING)
		printf("%s%ld %d is thinking%s\n", GREEN, t, id, NC);
	else if (code == EATING)
		printf("%s%ld %d is eating%s\n", BLUE, t, id, NC);
	else if (code == SLEEPING)
		printf("%s%ld %d is sleeping%s\n", PURPLE, t, id, NC);
	else if (code == TOOK_FORK)
		printf("%s%ld %d has taken a fork%s\n", YELLOW, t, id, NC);
}

int	print_messages(int code, unsigned int id, t_philo *philo)
{
	long	current_time;

	if (should_stop(philo, code))
		return (1);
	pthread_mutex_lock(&(philo->g->access_print_messages));
	if (code == DEAD)
	{
		current_time = getcurrenttime();
		if (current_time < 0)
		{
			pthread_mutex_unlock(&(philo->g->access_print_messages));
			return (1);
		}
		printf("%s%ld %d died%s\n", RED,
			current_time - philo->g->simulation_start, id, NC);
		pthread_mutex_lock(&(philo->g->access_stop_var_mutex));
		philo->g->stop = 1;
		pthread_mutex_unlock(&(philo->g->access_stop_var_mutex));
		pthread_mutex_unlock(&(philo->g->access_print_messages));
		return (1);
	}
	print_line(code, id, philo);
	pthread_mutex_unlock(&(philo->g->access_print_messages));
	return (0);
}

void	print_philo(t_philo *philo)
{
	printf("  [Philo %u]\n", philo->id);
	printf("    id              : %u\n", philo->id);
	printf("    last_meal_time  : %ld\n", philo->last_meal_time);
	printf("    time_to_die     : %u\n", philo->time_to_die);
	printf("    time_to_eat     : %u\n", philo->time_to_eat);
	printf("    time_to_sleep   : %u\n", philo->time_to_sleep);
	printf("    g ptr           : %p\n", (void *)philo->g);
}

void	print_global(t_global *g)
{
	int	i;

	printf("=== t_global ===\n");
	printf("  fork_mutex[1]: %p\n", g->fork_mutex[0]);
	printf("  fork_mutex[2]: %p\n", g->fork_mutex[1]);
	printf("  fork_mutex[3]: %p\n", g->fork_mutex[2]);
	printf("  fork_mutex[4]: %p\n", g->fork_mutex[3]);
	printf("  nb_of_philo  : %u\n", g->nb_of_philo);
	printf("  time_to_die  : %u\n", g->time_to_die);
	printf("  time_to_eat  : %u\n", g->time_to_eat);
	printf("  time_to_sleep: %u\n", g->time_to_sleep);
	printf("  nb_eat       : %d\n", g->max_eat);
	printf("  mutex ptr    : %p\n", (void *)g->fork_mutex);
	printf("  philo ptr    : %p\n", (void *)g->philo);
	printf("\n=== Philosophers ===\n");
	i = 0;
	while (i < g->nb_of_philo)
	{
		if (g->philo[i])
			print_philo(g->philo[i]);
		else
			printf("  [Philo %u] NULL\n", i);
		i++;
	}
}
