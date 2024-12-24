/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:29:24 by dakojic           #+#    #+#             */
/*   Updated: 2024/05/25 10:20:16 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_grab(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_right);
		printer(philo, "has taken a fork\n", 0);
		pthread_mutex_lock(philo->fork_left);
		printer(philo, "has taken a fork\n", 0);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		printer(philo, "has taken a fork\n", 0);
		pthread_mutex_lock(philo->fork_right);
		printer(philo, "has taken a fork\n", 0);
	}
}

void	fork_drop(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
}

void	eating(t_philo *philo)
{
	fork_grab(philo);
	if (dead_thread(0, philo))
	{
		fork_drop(philo);
		return ;
	}
	printer(philo, "is eating\n", 0);
	pthread_mutex_lock(&philo->set->eating);
	philo->last_meal = true_time();
	pthread_mutex_unlock(&philo->set->eating);
	true_sleep(philo->set->time_to_eat, philo);
	fork_drop(philo);
	pthread_mutex_lock(&philo->set->eating);
	philo->meals++;
	pthread_mutex_unlock(&philo->set->eating);
	printer(philo, "is sleeping\n", 0);
	true_sleep(philo->set->time_to_sleep, philo);
	printer(philo, "is thinking\n", 0);
	usleep(500);
}

void	*diner(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
	{
		printer(philo, "is thinking\n", 0);
		true_sleep(philo->set->time_to_die / 10, philo);
	}
	while (!dead_thread(0, philo))
	{
		if (philo->set->nbr_philo == 1)
		{
			lonely_philo(philo);
			break ;
		}
		eating(philo);
		if (philo->meals == philo->set->num_meals)
		{
			pthread_mutex_lock(&philo->set->dead);
			if (++philo->set->full == philo->set->nbr_philo)
				dead_thread(1, philo);
			pthread_mutex_unlock(&philo->set->dead);
		}
	}
	return (NULL);
}

void	lonely_philo(t_philo *philo)
{
	printer(philo, "grabs a fork\n", 0);
	true_sleep(philo->set->time_to_die, philo);
}
