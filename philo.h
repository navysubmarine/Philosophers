/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:17:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/21 16:22:06 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define TIMES_TO_COUNT 21000

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

typedef struct s_philo
{
	pthread_t		th;
	unsigned int	id;
	unsigned int	last_time_you_ate;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	struct s_global	*g;
	// bool			is_eating;
	// bool			is_thinking;
	// bool			is_dead;
}					t_philo;

typedef struct s_global
{
	t_philo			**philo;
	unsigned int	nb_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_eat;
	pthread_mutex_t	*mutex;
}					t_global;

/*HELPER*/
int					ft_atoi(const char *nptr);
/*CHECK ARGS*/
int					is_valid_number(char *arg);
int					check_arg(int argc, char **argv);
/*FREE*/
void				free_philos(t_philo **philo, unsigned int nb);