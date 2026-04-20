/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:17:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/04/16 11:28:46 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

#define TIMES_TO_COUNT 21000

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

typedef struct s_philo
{
    pthread_t  th;
    bool       is_eating;
    bool       is_thinking;
    bool       is_dead;
} t_philo;

typedef struct  s_global
{
    //pthread_t       **th;
    t_philo         **philo;
    unsigned int    nb_of_philo;
    unsigned int    time_to_die;
    unsigned int    time_to_eat;
    unsigned int    time_to_sleep;
    unsigned int    nb_eat;
}   t_global;

