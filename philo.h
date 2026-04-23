/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:17:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/23 15:52:00 by marthoma         ###   ########.fr       */
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
#define BLUE "\e[34m"
#define PURPLE "\e[35m"

typedef struct s_philo
{
	pthread_t		th;
	unsigned int	id;

	long			start;
	long			end;
	
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	struct s_global	*g;
}					t_philo;

typedef struct s_global
{
	t_philo			**philo;
	pthread_t		*supervisor;
	pthread_mutex_t	**fork_mutex;
	pthread_mutex_t	*ok_init_mutex;
	unsigned int	nb_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_eat;
	int				stop;
}					t_global;

/*HELPER*/
int					ft_atoi(const char *nptr);
/*CHECK ARGS*/
int					is_valid_number(char *arg);
int					check_arg(int argc, char **argv);
/*FREE*/
void				free_philos(t_philo **philo, unsigned int nb);
void				free_global(t_global *g);
/*PRINT*/
void				print_philo(t_philo *philo);
void				print_global(t_global *g);
