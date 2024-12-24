/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:29:31 by dakojic           #+#    #+#             */
/*   Updated: 2024/05/25 11:29:32 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_setter(t_s *set, int level)
{
	int	i;

	if (level >= 0)
	{
		pthread_mutex_destroy(&(set->eating));
		pthread_mutex_destroy(&(set->mutex_stop));
		pthread_mutex_destroy(&(set->stop_check));
		pthread_mutex_destroy(&(set->print));
		pthread_mutex_destroy(&(set->dead));
	}
	if (level >= 1)
		free(set->philo);
	if (level >= 2)
		free(set->forks);
}

int	check_av(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	philo_filler(t_s *set, int i)
{
	set->philo[i].id = i + 1;
	set->philo[i].stop = 0;
	set->philo[i].meals = 0;
	set->philo[i].fork_right = &(set->forks[i]);
	set->philo[i].set = set;
	set->philo[i].last_meal = 0;
}

int	starter_philo(t_s *set)
{
	int	i;

	i = -1;
	set->start = true_time();
	while (++i < set->nbr_philo)
	{
		philo_filler(set, i);
	}
	i = -1;
	while (++i < set->nbr_philo)
	{
		if (i + 1 == set->nbr_philo)
			set->philo[i].fork_left = &(set->forks[0]);
		else
			set->philo[i].fork_left = &(set->forks[i + 1]);
	}
	i = -1;
	while (++i < set->nbr_philo)
		pthread_create(&set->philo[i].tr_id, NULL, &diner, &set->philo[i]);
	i = -1;
	monitoring(set, 0);
	while (++i < set->nbr_philo)
		pthread_join(set->philo[i].tr_id, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_s				settings;
	pthread_mutex_t	big;

	if ((ac != 5 && ac != 6) || check_av(av))
	{
		printf("Error : args\n");
		return (1);
	}
	if (setter(&settings, av) == 1)
		return (1);
	starter_philo(&settings);
	free_setter(&settings, 3);
	return (0);
}
