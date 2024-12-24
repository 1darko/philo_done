/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:42:42 by dakojic           #+#    #+#             */
/*   Updated: 2024/05/25 10:24:41 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_fail(t_s *s, int flag)
{
	if (flag == 0)
	{
		pthread_mutex_destroy(&(s->eating));
		pthread_mutex_destroy(&(s->mutex_stop));
		pthread_mutex_destroy(&(s->stop_check));
	}
	if (flag == 1)
	{
		pthread_mutex_destroy(&(s->eating));
		pthread_mutex_destroy(&(s->mutex_stop));
		pthread_mutex_destroy(&(s->stop_check));
		pthread_mutex_destroy(&(s->print));
	}
}

int	settings_mutex_init(t_s *s)
{
	if (pthread_mutex_init(&(s->eating), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(s->mutex_stop), NULL) != 0)
	{
		pthread_mutex_destroy(&(s->eating));
		return (1);
	}
	if (pthread_mutex_init(&(s->stop_check), NULL) != 0)
	{
		pthread_mutex_destroy(&(s->eating));
		pthread_mutex_destroy(&(s->mutex_stop));
		return (1);
	}
	if (pthread_mutex_init(&(s->print), NULL) != 0)
	{
		mutex_fail(s, 0);
		return (1);
	}
	if (pthread_mutex_init(&(s->dead), NULL) != 0)
	{
		mutex_fail(s, 1);
		return (1);
	}
	return (0);
}

int	setter(t_s *set, char **av)
{
	int	i;

	i = -1;
	if (settings_mutex_init(set) || settings_filler(set, av))
		return (1);
	set->philo = malloc(sizeof(t_philo) * set->nbr_philo);
	if (!set->philo)
		return (free_setter(set, 0), 1);
	set->forks = malloc(sizeof(pthread_mutex_t) * set->nbr_philo);
	if (!(set->forks))
		return (free_setter(set, 1), 1);
	while (++i < set->nbr_philo)
	{
		if (pthread_mutex_init(&(set->forks[i]), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(set->forks[i]));
			return (free_setter(set, 2), 1);
		}
	}
	return (0);
}

void	settings_filler2(t_s *set, char **av)
{
	set->dead_philo = 0;
	set->start = true_time();
	set->big_stop = 0;
	set->nbr_philo = ft_atoi(av[1]);
	set->time_to_die = (long long int)ft_atoi(av[2]);
	set->time_to_eat = ft_atoi(av[3]);
	set->time_to_sleep = ft_atoi(av[4]);
	set->full = 0;
}

int	settings_filler(t_s *set, char **av)
{
	settings_filler2(set, av);
	if (av[5])
	{
		set->glutony = 0;
		set->num_meals = ft_atoi(av[5]);
		if (set->num_meals <= 0 || set->nbr_philo <= 0
			|| set->time_to_die < 0 || set->time_to_eat < 0
			|| set->time_to_sleep < 0)
			return (1);
	}
	else
	{
		set->glutony = 1;
		set->num_meals = -1;
	}
	if (set->nbr_philo <= 0)
		return (1);
	return (0);
}
