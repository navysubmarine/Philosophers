/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:17:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/27 16:35:45 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TIMES_TO_COUNT 21000

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"

# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define DEAD 4
# define TOOK_FORK 5

typedef struct s_philo
{
	pthread_t		th;
	unsigned int	id;

	int				times_ive_eaten;
	long			last_meal_time;

	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*access_last_meal_time;

	struct s_global	*g;
}					t_philo;

typedef struct s_global
{
	t_philo			**philo;
	pthread_t		supervisor;

	pthread_mutex_t	**fork_mutex;
	pthread_mutex_t	ok_init_mutex;
	pthread_mutex_t	access_stop_var_mutex;
	pthread_mutex_t	access_print_messages;
	pthread_mutex_t	access_philos_done;

	int				nb_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;

	int				philos_done;
	long			simulation_start;

	int				max_eat;

	int				stop;
}					t_global;

/*HELPER*/
int					ft_atoi(const char *nptr);
long				getcurrenttime(void);
/*CHECK ARGS*/
int					is_valid_number(char *arg);
int					check_arg(int argc, char **argv);
/*INIT STRUCTS*/
int					init(t_global *g, int argc, char **argv);
int					init_g_struct(t_global *g, int argc, char **argv);
int					init_g_mutex(t_global *g, pthread_mutex_t **mutex,
						unsigned int nb_of_philo);
int					init_philo(t_global *g, t_philo **philo,
						unsigned int nb_of_philo);
int					init_supervisor(t_global *g);
int					init_threads(t_global *g, t_philo **philo,
						unsigned int nb_of_philo);
/*ROUTINES*/
void				*routine_philo(void *data);
void				*routine_solo_philo(void *data);
void				*routine_supervisor(void *data);
/*ACTIONS*/
int					think(t_philo *philo);
int					eat(t_philo *philo);
int					my_sleep(t_philo *philo);
/*FREE*/
void				free_philos(t_philo **philo, unsigned int nb);
void				free_global(t_global *g);
/*PRINT*/
void				print_philo(t_philo *philo);
void				print_global(t_global *g);
int					print_messages(int code, unsigned int id, t_philo *philo);
#endif
