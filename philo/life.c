/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:32:15 by dakojic           #+#    #+#             */
/*   Updated: 2024/05/25 11:30:32 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_thread(int flag, t_philo *philo)
{
	pthread_mutex_lock(&(philo->set->stop_check));
	if (flag)
	{
		philo->set->big_stop = 1;
	}
	if (philo->set->big_stop)
	{
		pthread_mutex_unlock(&(philo->set->stop_check));
		return (1);
	}
	pthread_mutex_unlock(&(philo->set->stop_check));
	return (0);
}

static void	ded(t_s *set, int i)
{
	pthread_mutex_unlock(&set->dead);
	pthread_mutex_unlock(&set->eating);
	printer(&set->philo[i], "has died\n", 1);
	dead_thread(1, &set->philo[i]);
}

static void	lock_unlock(t_s *set, int flag)
{
	if (flag == 0)
	{
		pthread_mutex_lock(&set->eating);
		pthread_mutex_lock(&set->dead);
	}
	else
	{
		pthread_mutex_unlock(&set->dead);
		pthread_mutex_unlock(&set->eating);
	}
}

void	monitoring(t_s *set, int i)
{
	long long	time;
	t_philo		*philo;

	while (1)
	{
		philo = &set->philo[i];
		time = true_time();
		lock_unlock(set, 0);
		if (!dead_thread(0, philo)
			&& (time - philo->set->start) > set->time_to_die)
		{
			if (time - philo->last_meal >= set->time_to_die - 1)
			{
				ded(set, i);
				return ;
			}
		}
		lock_unlock(set, 1);
		if (dead_thread(0, &set->philo[i]))
			break ;
		if (i == set->nbr_philo)
			i = 0;
		if (set->nbr_philo > 30)
			usleep(100);
	}
}
