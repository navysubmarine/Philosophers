/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:19:29 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/20 19:10:38 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_number(char *arg)
{
    int i;

    i = 0;
    if (arg[i] == '-')
        return (0);
    while (arg[i] == '+')
        i++;
    while (arg[i])
    {
	    if (arg[i] >= '0' && arg[i] <= '9')
		   i++;
	    else
		    return (0);
    }
    return (1);
}

static int    check_arg(int argc, char **argv)
{
    int i;

    i = 1;
    if (argv[i][0] == '\0')
        return (1);
    if (argc != 5 && argc != 6)
    {
        printf("Error: expected format: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    while (i < argc)
    {
        if(!is_valid_number(argv[i]))
        {
            printf("Error: arguments must be positive numbers\n");
            return (1);
        }
        i++;
    }
    if (ft_atoi(argv[1]) < 1)
    {
        printf("Error: there must be at least one philosopher\n");
        return (1);
    }
    return (0);
}

static int init_philo(t_philo **philo, unsigned int nb_of_philo)
{
    unsigned int i;

    i = 0;
    while (i < nb_of_philo)
    {
        philo[i] = malloc(sizeof(t_philo));
        if (!philo[i])
            return (1);
        memset(philo[i], 0, sizeof(t_philo));
        i++;
    }
    return (0);
}

static int init_struct(t_global *g, int argc, char **argv)
{
    memset(g, 0, sizeof(t_global));
    g->nb_of_philo = ft_atoi(argv[1]);
    g->time_to_die = ft_atoi(argv[2]);
    g->time_to_eat = ft_atoi(argv[3]);
    g->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        g->nb_eat = ft_atoi(argv[5]);
    else
        g->nb_eat = -1;
    g->philo = malloc(sizeof(t_philo *) * g->nb_of_philo);
    if (!g->philo)
        return (1);
    if (init_philo(g->philo, g->nb_of_philo))
        return (1);
    return (0);
}   

int main(int argc, char **argv)
{
    t_global    g;
    if (check_arg(argc, argv))
        return (1);
    if (init_struct(&g, argc, argv))
        return (1);
}    

//  pthread_t tid1;
//  pthread_t tid2;
//  t_counter counter;

//  counter.count = 0;
//  pthread_mutex_init(&counter.count_mutex, NULL);
//  printf("Main: Le compte attendu est de %s%u%s\n", GREEN,
//      2 * TIMES_TO_COUNT, NC);

//  pthread_create(&tid1, NULL, thread_routine, &counter);
//  printf("Main: Creation du premier thread [%ld]\n", tid1);
//  pthread_create(&tid2, NULL, thread_routine, &counter);
//  printf("Main: Creation du second thread [%ld]\n", tid2);
//  pthread_join(tid1, NULL);
//  printf("Main: Union du premier thread [%ld]\n", tid1);
//  pthread_join(tid2, NULL);
//  printf("Main: Union du second thread [%ld]\n", tid2);
//  // Evaluation du compte final :
//  // (Ici on peut lire le compte sans s'occuper du mutex
//  // car tous les threads sont unis et on a la garantie
//  // qu'un seul un thread va y acceder.)
//  if (counter.count != (2 * TIMES_TO_COUNT))
//   printf("%sMain: ERREUR ! Le compte est de %u%s\n",
//      RED, counter.count, NC);
//  else
//   printf("%sMain: OK. Le compte est de %u%s\n",
//      GREEN, counter.count, NC);
//  pthread_mutex_destroy(&counter.count_mutex);
//  return (0);
