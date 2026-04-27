/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:31:58 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/27 14:45:57 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_messages(int code, unsigned int id, t_philo *philo)
{
	static int	death_has_occurred = 0;
	long		current_time;

	pthread_mutex_lock(&(philo->g->access_print_messages));
	current_time = getcurrenttime();
	if (!current_time)
		return ;
	if (!death_has_occurred)
	{
		if (code == 1)
			printf("%s%ld %d is thinking%s\n", GREEN, current_time
				- philo->g->simulation_start, id, NC);
		else if (code == 2)
			printf("%s%ld %d is eating%s\n", BLUE, current_time
				- philo->g->simulation_start, id, NC);
		else if (code == 3)
			printf("%s%ld %d is sleeping%s\n", PURPLE, current_time
				- philo->g->simulation_start, id, NC);
		else if (code == 4)
		{
			printf("%s%ld %d died%s\n", RED, current_time
				- philo->g->simulation_start, id, NC);
			death_has_occurred = 1;
		}
		else if (code == 5)
		{
			printf("%s%ld %d has taken a fork%s\n", YELLOW, current_time
				- philo->g->simulation_start, id, NC);
		}
	}
	pthread_mutex_unlock(&(philo->g->access_print_messages));
}

void	print_philo(t_philo *philo)
{
	printf("  [Philo %u]\n", philo->id);
	printf("    id              : %u\n", philo->id);
	printf("    start			 : %ld\n", philo->start);
	printf("    last_meal_time  : %ld\n", philo->last_meal_time);
	printf("    time_to_die     : %u\n", philo->time_to_die);
	printf("    time_to_eat     : %u\n", philo->time_to_eat);
	printf("    time_to_sleep   : %u\n", philo->time_to_sleep);
	// printf("    left_fork  ptr  : %p\n", (void *)philo->left_fork);
	// printf("    right_fork  ptr : %p\n", (void *)philo->right_fork);
	printf("    g ptr           : %p\n", (void *)philo->g);
}

void	print_global(t_global *g)
{
	int i;

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